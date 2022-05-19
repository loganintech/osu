-- Team Members - Logan Saso

module LSasoHomeworkFour where

type Prog = [Cmd]
data Cmd = LD Int
         | ADD
         | MULT
         | DUP
         | INC
         | SWAP
         | POP Int

type Rank = Int
type CmdRank = (Int, Int)

rankC :: Cmd -> CmdRank
rankC (LD _)  = (0, 1)
rankC ADD     = (2, 1)
rankC MULT    = (2, 1)
rankC DUP     = (1, 2)
rankC INC     = (1, 1)
rankC SWAP    = (2, 2)
rankC (POP x) = (x, 0)

rankP :: Prog -> Maybe Rank
rankP x = rank x 0

rank :: Prog -> Rank -> Maybe Rank
rank (c : cs) r
    | r >= fst (rankC c) = rank cs (r - fst (rankC c) + snd (rankC c))
    | otherwise          = Nothing
rank [] r = Just r



-- semStatTC :: Prog -> Maybe Int
-- semStatTC p | rankP p /= Nothing = Just (sem p)
--             | otherwise          = Nothing

-- Since this function checks whether or not the rank of the program is valid first, we don't need to check that during SEM's operation and therefore Sem doesn't have to return a 'maybe' type

{-

    Exercise 2. Shape Language

-}

data Shape = X
    | TD Shape Shape
    | LR Shape Shape
    deriving Show

-- Width by Height
type BBox = (Int, Int)

bbox :: Shape -> BBox
bbox X = (1, 1)
bbox (TD s s2) =
    (max (fst (bbox s)) (fst (bbox s2)), snd (bbox s) + snd (bbox s2))
bbox (LR s s2) =
    (fst (bbox s) + fst (bbox s2), max (snd (bbox s)) (snd (bbox s2)))


rect :: Shape -> Maybe BBox
rect X = Just (1, 1)
-- If you want to put a rect on top of another, it must have the same width
rect (TD s s2) | fst (bbox s) == fst (bbox s2) = Just (bbox (TD s s2))
-- If you want to put a rect on the left side of another, it must have the same height
rect (LR s s2) | snd (bbox s) == snd (bbox s2) = Just (bbox (LR s s2))
rect _ = Nothing


{-

    Exercise 3. Parametric Polymorphism

-}

-- Consider the following
f x y = if null x then [y] else x
g x  y = if not (null x) then [] else [y]
g [] y = []

-- Question A
-- F returns a list of the same type as both of its arguments ([a] and a respectively)
-- G returns a list of the same type as its second argument, the first is thrown out
-- part 2
-- F has this type because it either returns a list of its second argument or its first argument, so they must be the same type
-- G has this type because it either returns a list of its second argument or an empty list, so its always the same type as the second param
-- part 3
-- G is more general because it can accept arguments that contain different types
-- part 4
-- They have different types because f returns its first argument, binding the second to be the same type as the first


h x y = if not (null y) then map snd y else x

k f1 f2 = f1 (f2 f1)

-- Part D a -> b
-- It's very difficult to convert a generic type to a generic other type. This could be done with conversion functions like `even` that map from a generic type to a specific type.
