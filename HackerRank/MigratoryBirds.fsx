open System.IO
let ParseNums input = 
    (File.ReadAllText input).Split(' ')
    |> Array.map int

let Answer input = 
    input 
    |> Array.groupBy id 
    |> Array.maxBy (fun (_,xs) -> Array.length xs)
    |> fun (_,xs) -> Array.head xs

Answer (ParseNums "nums.txt")