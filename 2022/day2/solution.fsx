open System.IO

let filePath = "input.txt"

let lines = File.ReadLines(filePath) |> Seq.toList

let calcGamePart1 s = 
    match s with
    | "A X" -> 1+3
    | "A Y" -> 2+6
    | "A Z" -> 3+0
    | "B X" -> 1+0
    | "B Y" -> 2+3
    | "B Z" -> 3+6
    | "C X" -> 1+6
    | "C Y" -> 2+0
    | "C Z" -> 3+3
    | _ -> -999999999

let calcGamePart2 s = 
    match s with
    | "A X" -> 0+3
    | "A Y" -> 3+1
    | "A Z" -> 6+2
    | "B X" -> 0+1
    | "B Y" -> 3+2
    | "B Z" -> 6+3
    | "C X" -> 0+2
    | "C Y" -> 3+3
    | "C Z" -> 6+1
    | _ -> -999999999



let rec main calcGame lines = 
    List.fold (fun solution line -> solution + calcGame line) 0 lines
    (*
    match lines with
    | [] -> 0
    | s::l -> calcGame s + main calcGame l 
    *)



printfn "Part 1: %d" (main calcGamePart1 lines) 
printfn "Part 2: %d" (main calcGamePart2 lines) 