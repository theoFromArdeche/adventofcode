const fs = require('node:fs');


fs.readFile('input.txt', 'utf8', (err, data) => {
    if (err) {
      console.error(err);
      return;
    }
    const backpacks = data.trim().split('\n');
    console.log("Part 1 solution : ", part1(backpacks));
    console.log("Part 2 solution : ", part2(backpacks));
});


function part1(backpacks) {
    var answer=0;
    for (var backpack of backpacks) {
        var [countMin, countMaj] = count(backpack.substring(0, backpack.length/2));
        
        var [tempCountMin, tempCountMaj] = count(backpack.substring(backpack.length/2));
        countMin&=tempCountMin; countMaj&=tempCountMaj;
        
        if (countMin!=0) answer+= Math.log2(countMin)+1;
        else answer+= Math.log2(countMaj)+27;
    }
    return answer;
}


function part2(backpacks) {
    var answer=0;
    for (var i=0; i<backpacks.length/3; i++) {
        var [countMin, countMaj] = count(backpacks[i*3]);

        var [tempCountMin, tempCountMaj] = count(backpacks[i*3+1]);
        countMin&=tempCountMin; countMaj&=tempCountMaj;

        [tempCountMin, tempCountMaj] = count(backpacks[i*3+2]);
        countMin&=tempCountMin; countMaj&=tempCountMaj;
        
        if (countMin!=0) answer+= Math.log2(countMin)+1;
        else answer+= Math.log2(countMaj)+27;
    }
    return answer;
}


function count(data) {
    return Array.from(data).reduce(([countMin, countMaj], c) => {
        if (c >= 'a') return [countMin|2**(c.charCodeAt(0)-'a'.charCodeAt(0)), countMaj]
        else return [countMin, countMaj|2**(c.charCodeAt(0)-'A'.charCodeAt(0))]
    }, [0, 0])
}