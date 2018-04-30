fun member (x, []) = false
|   member (x, el::list) =
    if x = el then
        true
    else member (x, list)


fun subset ([], list) = true
|   subset (x::l1, l2) =
    if member (x, l2) then
        subset (l1, l2)
    else false


fun equal (x, y) = subset(x, y) andalso subset(y, x)

fun union ([], y) = y
|   union (x::l, y) =
    if member (x, y) then
        union (l, y)
    else x::union (l, y)


fun parse file =
    let
        fun next_int input =
            Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)
        val stream = TextIO.openIn file
        val n = next_int stream
        fun scanner 0 acc = acc
        |   scanner i acc =
            let
                val d = next_int stream
            in
                scanner (i - 1) (d :: acc)
            end
    in
        rev(scanner n [])
    end

structure foo = struct
    type t = string
    val say = fn x => TextIO.print x
end

fun test () =
    let
        val lol = 1
        val lel = 2
    in
        if lol = 1 then
            true
        else
            false
    end
