fun max(a,b) = if a > b then a else b

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


fun getMaxlist ([], maxlist) = tl(rev(maxlist))
|   getMaxlist (l, maxlist) =
if hd(l) > hd(maxlist) then
    getMaxlist (tl(l), hd(l)::maxlist)
else
    getMaxlist (tl(l), hd(maxlist)::maxlist)


fun getMinlist ([], minlist) = tl(rev(minlist))
|   getMinlist (l, minlist) =
if hd(l) < hd(minlist) then
    getMinlist (tl(l), hd(l)::minlist)
else
    getMinlist (tl(l), hd(minlist)::minlist)


fun process ([], l2, distance, i, j) = distance
|   process (l1, [], distance, i, j) = distance
|   process (l1, l2, distance, i, j) =
if hd(l1) < hd(l2)
then
    process (l1, tl(l2), distance, i, j+1)
else
    process (tl(l1), l2, max(distance, i-j), i+1, j)


fun skitrip infile =
let
    val inputlist = parse infile
    val revinputlist = rev(inputlist)
    val l1 = rev(getMaxlist (revinputlist, [(hd(revinputlist))]))
    val l2 = getMinlist(inputlist, [hd(inputlist)])
in
    process (l1, l2, 0, 0, 0)
end
