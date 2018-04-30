fun reverse xs =
    let
        fun rev (nil,z) = z
        |   rev (y::ys, z) = rev (ys, y::z)
    in
        rev (xs, nil)
    end

(* last element of a list *)
fun last (list) = hd (reverse (list));

(* length of a list *)
fun len nil = 0
|   len (x::l) = len(l) + 1;

(* sum of the elements of a list *)
fun sum nil = 0
|   sum (h::t) =
    h + sum t

(* Number of elements in list which satisfy a condition *)
fun ctrue nil = 0
|   ctrue (true::l) = 1 + ctrue(l)
|   ctrue (false::l) = ctrue(l)

(* Takes a list and returns a tuple of 2 lists, each holding
the lower and upper half of the original, respectively *)
fun halve [] = ([], [])
|   halve [a] = ([a], [])
|   halve (a::b::cs) =
    let
        val (x, y) = halve (cs)
    in
        (a::x, b::y)
    end

(* Mergesort (uses halve) *)
fun mergesort nil = nil
|   mergesort [a] = [a]
|   mergesort list =
    let
        val (x, y) = halve list
        fun merge (nil, ys) = ys
        |   merge (xs, nil) = xs
        |   merge (x::xs, y::ys) =
            if x < y then
                x::merge(xs, y::ys)
            else
                y::merge(x::xs, ys)
    in
        merge (mergesort x, mergesort y)
    end

(* Maps a function onto each element of a list *)
fun map (f, []) = []
|   map (f, x::list) =
    f(x)::map(f, list)

(* Takes a list of lists and flattens it *)
fun flat [] = []
|   flat (l::ls) = l @ flat ls;

(* true if x is in list *)
fun ismember (x, []) = false
|   ismember (x, l::ls) =
    if x = l then true
    else ismember (x, ls)

(* classic foldl (f takes two args as tuple)*)
fun foldl f i list =
    let
        fun fold (f, prev, []) = prev
        |   fold (f, prev, x::list) =
            fold (f, f(prev,x), list)
    in
        fold (f, i, list)
    end

(* using foldl to implement foldr *)
fun foldr f i list =
    let
        val r = reverse(list)
    in
        foldl f i r
    end
