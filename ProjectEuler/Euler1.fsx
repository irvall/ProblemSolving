(* If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000. *)

let sumUpTo n = (n * (n+1)) / 2

let multipleOfMN m n t =
    let (a,b,c) = sumUpTo ((t-1)/m), sumUpTo ((t-1)/n), sumUpTo ((t-1)/(m*n))
    a * m + b * n - c * m * n

multipleOfMN 3 5 1000
// val it : int = 233168
