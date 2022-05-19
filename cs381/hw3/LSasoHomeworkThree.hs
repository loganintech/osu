-- Team Members - Logan Saso

module LSasoHomeworkThree where

type Prog = [Cmd]

-- This includes the modified type for in 2b
-- Trying to run sem on a program with DEF or CALL will result in a compiler error
data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         | DEF String Prog
         | CALL String

type Stack = [Int]

sem :: Prog -> Maybe Stack -> Maybe Stack
sem _          Nothing  = Nothing
sem (c : cmds) (Just x) = sem cmds $ semCMD c x
sem []         x        = x


semCMD :: Cmd -> Stack -> Maybe Stack

semCMD (LD x) []           = Just [x]
semCMD (LD x) s            = Just $ x : s
semCMD ADD    []           = Nothing
semCMD ADD    [_         ] = Nothing
semCMD ADD    (x : y : xs) = Just $ x + y : xs
semCMD MULT   []           = Nothing
semCMD MULT   [_         ] = Nothing
semCMD MULT   (x : y : xs) = Just $ x * y : xs
semCMD DUP    []           = Nothing
semCMD DUP    (x : xs)     = Just $ x : x : xs


{-

    EXERCISE 2 Extending the Stack Language

-}


type Macros = [(String, Prog)]

type State = (Stack, Macros)

sem2 :: Prog -> Maybe State -> Maybe Stack

sem2 _          Nothing       = Nothing
sem2 []         (Just (s, _)) = Just s
sem2 (c : cmds) (Just s     ) = sem2 cmds $ semCMD2 c s

semCMD2 :: Cmd -> State -> Maybe State

semCMD2 (LD x)    ([]        , m ) = Just ([x], m)
semCMD2 (LD x)    (s         , m ) = Just (x : s, m)
semCMD2 ADD       ([]        , _ ) = Nothing
semCMD2 ADD       ([     _ ] , _ ) = Nothing
semCMD2 ADD       (x : y : xs, m ) = Just (x + y : xs, m)
semCMD2 MULT      ([]        , _ ) = Nothing
semCMD2 MULT      ([     _ ] , _ ) = Nothing
semCMD2 MULT      (x : y : xs, m ) = Just (x * y : xs, m)
semCMD2 DUP       ([]        , _ ) = Nothing
semCMD2 DUP       (x : xs    , m ) = Just (x : x : xs, m)
semCMD2 (DEF s p) (x         , m ) = Just (x, (s, p) : m)
semCMD2 (CALL _ ) (_         , []) = Nothing
semCMD2 (CALL s) (x, (mn, p) : ms)
    | mn == s = case sem2 p (Just (x, (mn, p) : ms)) of
        Just g  -> Just (g, (mn, p) : ms)
        Nothing -> Nothing
    | otherwise = semCMD2 (CALL s) (x, ms ++ [(mn, p)])


-- Output is 729 -- ((3^2)*3)^2
sem2Test =
    [ LD 3
    , DEF "sqr"  [DUP, MULT]
    , DEF "trip" [LD 3, MULT]
    , CALL "sqr"
    , CALL "trip"
    , CALL "sqr"
    ]


{-

    Exercise 3

-}


data LogoCmd = Pen Mode
    | MoveTo Int Int
    | Seq LogoCmd LogoCmd

data Mode = Up | Down

type LogoState = (Mode, Int, Int)
type Line = (Int, Int, Int, Int)
type Lines = [Line]


semS :: LogoCmd -> LogoState -> (LogoState, Lines)
semS (Pen Up) (_, x, y) = ((Up, x, y), [])
semS (Pen Down) (_, x, y) = ((Down, x, y), [])
semS (MoveTo a b) (Down, x, y) = ((Down, a, b), [(x, y, a, b)])
semS (MoveTo a b) (Up, x, y) = ((Up, a, b), [])
semS (Seq a b) s = do
    let (fs, fl) = semS a s
    let (ss, sl) = semS b fs
    (ss, fl ++ sl)

sem' :: LogoCmd -> Lines
sem' a = snd $ semS a (Up, 0, 0)


semSTest :: LogoCmd
semSTest = (Pen Down) `Seq` (MoveTo 3 2) `Seq` (Pen Up) `Seq` (MoveTo 4 4) `Seq` (Pen Down) `Seq` (MoveTo 7 7)
