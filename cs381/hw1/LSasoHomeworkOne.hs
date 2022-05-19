-- Team Members - Logan Saso

module LSasoHomeworkOne where

type Bag a = [(a, Int)]

-- Question A -- Inserts some item A into a bag
ins :: Eq a => a -> Bag a -> Bag a
ins a [] = [(a, 1)]
ins a ((aTwo, b) : bs) | a == aTwo = (aTwo, b + 1) : bs
                       | otherwise = (aTwo, b) : ins a bs

-- Question B -- Removes some item B from a bag
del :: Eq a => a -> Bag a -> Bag a
del _ [] = []
del a ((aTwo, b) : bs) | a == aTwo && b > 1  = (aTwo, b - 1) : bs
                       | a == aTwo && b == 1 = bs
                       | otherwise           = (aTwo, b) : del a bs

-- Question C -- Converts a list of entries into a bag of the same entries
bag :: Eq a => [a] -> Bag a
bag = foldr ins []

-- Question D -- Determines if a bag is a subbag of another
subbag :: Eq a => Bag a -> Bag a -> Bool
subbag [] _  = True
subbag _  [] = False
subbag ((a, b) : bs) ((x, y) : xs)
    | a == x && b > y = False
    | a == x && b <= y = True && subbag bs xs
    | otherwise =  any (\(g, h) -> a == g && b <= h) ((x, y) : xs)
    && subbag bs ((x, y) : xs)


-- Question E -- Compute the intersection of two multisets
isbag :: Eq a => Bag a -> Bag a -> Bag a
isbag [] _  = []
isbag _  [] = []
isbag ((a, av) : as) ((b, bv) : bs)
    | a == b              = (a, av + bv) : isbag as bs
    | subbag [(a, av)] bs = isbag ((a, av) : as) bs
    | subbag [(b, bv)] as = isbag as ((b, bv) : bs)
    | otherwise           = isbag as bs


-- Question F -- Define a function size that computes the number of elements in a bag
size :: Bag a -> Int
size = foldr (\(_, b) acc -> b + acc) 0

{-

    EXERCISE 2 GRAPHS

-}

type Node = Int
type Edge = (Node, Node)
type Graph = [Edge]
type Path = [Node]

-- Question A -- Define the function nodes that computes the list of nodes contained in a graph
nodes :: Graph -> Path
nodes = foldr
    (\(n1, n2) l -> ([ n1 | n1 `notElem` l ] ++ [ n2 | n2 `notElem` l ]) ++ l)
    []

-- Question B -- Define the function suc that computes the list of successors for a node in a given graph
suc :: Node -> Graph -> [Node]
suc _ [] = []
suc n ((e, s) : gs) | n == e    = s : suc n gs
                    | otherwise = suc n gs


-- Question C -- Define the function detatch that removes a node with all of its incident edges from a graph
detach :: Node -> Graph -> Graph
detach _ [] = []
detach n ((t, f) : es) | n == t || n == f = detach n es
                       | otherwise        = (t, f) : detach n es


-- Question D -- Define the function cyc that creates a cycle of any given length
-- cyc 1 = [(1, 1)]
-- cyc 2 = [(1, 2), (2, 1)]
-- cyc 3 = [(1, 2), (2, 3), (3, 1)]
cyc :: Int -> Graph
cyc 0 = []
cyc a = init (zip [1 .. a] [2 .. a + 1]) ++ [(a, 1)]


{-

    EXERCISE 3 PROGRAMMING WITH DATA TYPES

-}

type Number = Int

type Point = (Number, Number)
type Length = Number

data Shape = Pt Point
        | Circle Point Length
        | Rect Point Length Length
        deriving Show
type BBox = (Point, Point)

-- Question A -- Define the function width that computes the width of a shape
width :: Shape -> Length
width (Pt (_, _)      ) = 0
width (Circle (_, _) r) = 2 * r
width (Rect (_, _) w _) = w

-- Question B -- Define the function bbox that computes the bounding box of the shape
bbox :: Shape -> BBox
bbox (Pt (x, y)      ) = ((x, y), (x, y))
bbox (Circle (x, y) r) = ((x - r, y - r), (x + r, y + r))
bbox (Rect (x, y) w h) = ((x, y), (x + w, y + h))

-- Question C -- Define the function minX that computes the minimum x coordinate of a shape
minX :: Shape -> Number
minX a = fst $ fst $ bbox a

-- Question D -- Define the function move that moves the position of the shape by a vector given as a point as its second argument
move :: Shape -> Point -> Shape
move (Pt (x, y)      ) (x2, y2) = Pt (x + x2, y + y2)
move (Circle (x, y) r) (x2, y2) = Circle (x + x2, y + y2) r
move (Rect (x, y) w h) (x2, y2) = Rect (x + x2, y + y2) w h



-- Question E -- Define a function alignLeft that transforms one figure into another in which all shapes have the same minX
type Figure = [Shape]

-- Lil auxilary function to make alignLeft better
moveToX :: Shape -> Int -> Shape
moveToX (Pt (_, y)      ) newX = Pt (newX, y)
moveToX (Circle (_, y) r) newX = Circle (newX + r, y) r
moveToX (Rect (_, y) w h) newX = Rect (newX, y) w h


alignLeft :: Figure -> Figure
alignLeft a = map (`moveToX` (minimum $ map minX a)) a

-- Question F -- Define a function inside that checks whether one shape is inside of another, that is, whether the bbox of the first is smaller than the second
inside :: Shape -> Shape -> Bool
inside a b = do
    let (((x1, y1), (x2, y2)), ((x3, y3), (x4, y4))) = (bbox a, bbox b)
    x1 >= x3 && y1 >= y3 && x2 <= x4 && y2 <= y4
