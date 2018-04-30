signature UNIONFIND =
    sig
        type t

        val create : int -> t
        val union : t * int * int -> unit
        val connected : t * int * int -> bool
    end


structure QuickUnion :> UNIONFIND = struct

    open Array

    type t = int array

    fun create n =
        tabulate (n, fn x => x)

    fun root (id, n) =
        let
            val i = ref n
        in
            (while !i <> sub (id, !i) do i := sub (id, !i); !i)
        end

    fun connected (id, p, q) =
        root (id, p) = root (id, q)

    fun union (id, p, q) =
        let
            val i = root (id, p)
            val j = root (id, q)
        in
            update (id, i, j)
        end
    end


structure ufd = QuickUnion
val groups = ufd.create (2000000);

fun next_int input =
    Option.valOf (TextIO.scanStream (Int.scan StringCvt.DEC) input)


fun answer (num_groups, K ) =
    let
        val diff = num_groups - K;
    in
        if diff < 1 then 1
        else diff
    end


fun resolve (x, y) = y;


fun get_num_groups (0, stream, groups, result) = result
|   get_num_groups (M, stream, groups, result) =
    let
        val first = next_int stream
        val second = next_int stream
    in
        if ufd.connected (groups, first, second) then
            resolve ((), get_num_groups ((M - 1), stream, groups, result))
        else
            resolve (ufd.union (groups, first, second),
            get_num_groups ((M - 1), stream, groups, (result - 1)))
    end


fun villages infile =
    let
        val stream = TextIO.openIn infile

        val N = next_int stream
        val M = next_int stream
        val K = next_int stream

        val num_groups = get_num_groups (M, stream, groups, N)
    in
        answer (num_groups, K)
    end
