#import <Foundation/Foundation.h>


int main() {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSString *filePath = @"input.txt";

    NSError *error = nil;

    NSString *fileContents = [
        NSString stringWithContentsOfFile:filePath 
        encoding:NSUTF8StringEncoding 
        error:&error
    ];

    if (error) {
        NSLog(@"Error reading file: %@", [error localizedDescription]);
        [pool drain];
        return 0;
    }


    NSArray *lines = [fileContents componentsSeparatedByString:@"\n"];
    NSMutableArray *stacksPart1 = [NSMutableArray arrayWithCapacity:9];
    NSMutableArray *stacksPart2 = [NSMutableArray arrayWithCapacity:9];
    NSInteger size = -1;

    for (NSString *line in lines) {
        if ([line length] == 0) break;
        size +=1;
    }

    //NSLog(@"%d", size);

    for (int i=0; i<9; i++) {
        NSMutableArray *subArrayPart1 = [NSMutableArray arrayWithCapacity:9*size];
        NSMutableArray *subArrayPart2 = [NSMutableArray arrayWithCapacity:9*size];
        [stacksPart1 addObject:subArrayPart1];
        [stacksPart2 addObject:subArrayPart2];
    }


    for (NSString *line in lines) {
        if ([line length] == 0 || [line hasPrefix:@" 1"]) break;
        for (int i=0; i<9; i++) {
            NSString *e = [line substringWithRange:NSMakeRange(i * 4 + 1, 1)];
            if (![e isEqualToString:@" "]) {
                [[stacksPart1 objectAtIndex:i] insertObject:e atIndex:0];
                [[stacksPart2 objectAtIndex:i] insertObject:e atIndex:0];
            }
        }
    }
    
    //for (int i = 0; i < 9; i++) {
    //    NSLog(@"Stack1 %d: %@", i + 1, [stacksPart1 objectAtIndex:i]);
    //}
    //for (int i = 0; i < 9; i++) {
    //    NSLog(@"Stack2 %d: %@", i + 1, [stacksPart2 objectAtIndex:i]);
    //}

    NSInteger skipLines = size+2;

    for (NSString *line in lines) {
        if (skipLines > 0 || [line length] == 0) {
            skipLines-=1;
            //NSLog(@"skipped line : %@", line);
            continue;
        }  
        
        NSArray *components = [line componentsSeparatedByString:@" "];
        NSInteger count = [[components objectAtIndex:1] integerValue];
        NSInteger fromStack = [[components objectAtIndex:3] integerValue] - 1;
        NSInteger toStack = [[components objectAtIndex:5] integerValue] - 1;

        //NSLog(@"move %d from %d to %d", count, fromStack+1, toStack+1);

        NSMutableArray *temp = [NSMutableArray arrayWithCapacity:9*size];


        for (NSInteger i=0; i<count; i++) {
            NSString *stackPart1 = [[stacksPart1 objectAtIndex:fromStack] lastObject];
            [[stacksPart1 objectAtIndex:fromStack] removeLastObject];
            [[stacksPart1 objectAtIndex:toStack] addObject:stackPart1];

            NSString *stackPart2 = [[stacksPart2 objectAtIndex:fromStack] lastObject];
            [[stacksPart2 objectAtIndex:fromStack] removeLastObject];
            [temp addObject:stackPart2];
        }

        for (NSInteger i=0; i<count; i++) {
            NSString *stackPart2 = [temp lastObject];
            [temp removeLastObject];
            [[stacksPart2 objectAtIndex:toStack] addObject:stackPart2];
        }
    }



    //for (int i = 0; i < 9; i++) {
    //    NSLog(@"Stack1 %d: %@", i + 1, [stacksPart1 objectAtIndex:i]);
    //}
    //for (int i = 0; i < 9; i++) {
    //    NSLog(@"Stack2 %d: %@", i + 1, [stacksPart2 objectAtIndex:i]);
    //}

    NSMutableString *topStacksPart1 = [NSMutableString string];
    NSMutableString *topStacksPart2 = [NSMutableString string];
    for (int i=0; i<9; i++) {
        NSString *topPart1 = [[stacksPart1 objectAtIndex:i] lastObject];
        if (topPart1) [topStacksPart1 appendString:topPart1];

        NSString *topPart2 = [[stacksPart2 objectAtIndex:i] lastObject];
        if (topPart2) [topStacksPart2 appendString:topPart2];
        
    }
    NSLog(@"Part 1 solution : %@", topStacksPart1);
    NSLog(@"Part 2 solution : %@", topStacksPart2);

    [pool drain];
    return 0;
}