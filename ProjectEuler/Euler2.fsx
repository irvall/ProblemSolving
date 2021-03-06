(*  Each new term in the Fibonacci sequence is generated by adding the previous two terms. 
    By starting with 1 and 2, the first 10 terms will be:

        1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

    By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.*)

let fibo =
    let rec fibo' p c sum =
        match p with
        | n when n > int 4e6 -> sum
        | _ -> if p % 2 = 0 then
                fibo' c (c+p) (p+sum) 
               else
                fibo' c (c+p) sum
    fibo' 1 2 0
//val fibo : int = 4613732
