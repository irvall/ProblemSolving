let sumUpTo n = (n * (n+1)) / 2

let multipleOfMN m n t =
    let (a,b,c) = sumUpTo ((t-1)/m), sumUpTo ((t-1)/n), sumUpTo ((t-1)/(m*n))
    a * m + b * n - c * m * n

multipleOfMN 3 5 1000
// val it : int = 233168
