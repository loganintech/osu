-- Team Members - Logan Saso

module LSasoHomeworkTwo where

{-

    Exercise 1. Mini Logo

-}

-- (a) Define the abstract syntax for Mini Logo as a Haskell data type
data Cmd = Pen Mode
        | MoveTo (Pos, Pos)
        | Def String Params Cmd
        | Call String Vals
        | Chain Cmd Cmd
    deriving Show

data Mode = Up | Down
    deriving Show
data Pos = PosNum Int | ParamName String
    deriving Show
data Params = Param String Params | LastParam String
    deriving Show
data Vals = IntVals Int Vals | ValsChars String
    deriving Show

-- (b) Write a Mini Logo macro vector that draws a line from a given position (x1, y1) to a given position (x2, y2)
vectors :: Cmd
vectors = Def
    "vector"
    (Param "x1" (Param "y1" (Param "x2" (LastParam "y2"))))
    (Chain (Chain (MoveTo (ParamName "x1", ParamName "y1")) (Pen Down))
           (Chain (MoveTo (ParamName "x2", ParamName "y2")) (Pen Up))
    )

-- (c) Define a Haskell function steps that constructs a Mini Logo program which draws a stair of n steps.
-- Your solution should not use the macro vector.

steps :: Int -> Cmd
steps a = Chain (Chain (MoveTo (PosNum a, PosNum a)) (Pen Down)) (innersteps a)


innersteps :: Int -> Cmd
innersteps a
    | a > 0 = Chain
        (Chain (MoveTo (PosNum (a - 1), PosNum a))
               (MoveTo (PosNum (a - 1), PosNum (a - 1)))
        )
        (innersteps (a - 1))
    | otherwise = Pen Up

{-

    Exercise 2. Digital Circuit Design Language

-}

-- (a) Define the abstract syntax for the above language as a Haskell data type.
data Circuit = Gate Gates Links

data Gates = Fn Int GameFn | FnMore Int GameFn Gates
instance Show Gates where
    show (Fn x y      ) = show x ++ ":" ++ show y ++ ";"
    show (FnMore x y z) = show x ++ ":" ++ show y ++ ";" ++ "\n" ++ show z

data GameFn = And | Or | Xor | Not
instance Show GameFn where
    show And = "and"
    show Or  = "or"
    show Xor = "xor"
    show Not = "not"

data Links = Link (Int, Int) (Int, Int) | MoreLinks (Int, Int) (Int, Int) Links
instance Show Links where
    show (Link (x1, y1) (x2, y2)) =
        "from "
            ++ show x1
            ++ "."
            ++ show y1
            ++ " to "
            ++ show x2
            ++ "."
            ++ show y2
            ++ ";"
    show (MoreLinks (x1, y1) (x2, y2) z) =
        show (Link (x1, y1) (x2, y2)) ++ "\n" ++ show z

-- (b) Represent the half adder circuit as a Haskell data type value
halfAdder :: Circuit
halfAdder = Gate (FnMore 1 Xor (Fn 2 And))
                 (MoreLinks (1, 1) (2, 1) (Link (1, 2) (2, 2)))

-- (c) Define a Haskell function that implements a pretty printer for the abstract syntax
prettyPrintCircuit :: Circuit -> IO ()
prettyPrintCircuit (Gate x y) = putStrLn (show x ++ "\n" ++ show y)

{-

    Exercise 3. Designing Abstract Syntax

-}

data Expr = N Int
    | Plus Expr Expr
    | Times Expr Expr
    | Neg Expr
    deriving Show


data Op = Add | Multiply | Negate
    deriving Show


data Exp = Num Int
    | Apply Op [Exp]
    deriving Show

-- (a) Represent the expression -(3+4)*7 in the alternative syntax tree
athree :: Exp
athree = Apply Multiply [Apply Negate [Apply Add [Num 3, Num 4]], Num 7]

-- (b) What are the advantages or disadvantages for either representation?
{-
    The first representation is convinent because it is structured very much like a math statement.
    Each expression is the same type so they can be joined nicely. However, it doesn't give us much safety on order.

    The second representation can apply arguments to arbitrary numbers of arguments.
    This is nice programatically but it doesn't represent the two-at-a-time nature of these expressions
-}

-- (c) Define a function translate :: Expr -> Exp that translates expressions given in the first abstract syntax
-- into equivalent expressions in the second abstract syntax
translate :: Expr -> Exp
translate (N x      ) = Num x
translate (Plus  x y) = Apply Add [translate x, translate y]
translate (Times x y) = Apply Multiply [translate x, translate y]
translate (Neg x    ) = Apply Negate [translate x]
