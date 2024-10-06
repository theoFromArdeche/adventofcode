const std = @import("std");

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    var file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    const file_size = try file.getEndPos();
    const buffer = try allocator.alloc(u8, file_size);
    defer allocator.free(buffer);

    _ = try file.readAll(buffer);

    //std.debug.print("File content:\n{s}\n", .{buffer});

    var count: u32 = 0;
    var start: u32 = 0;
    var index: usize = 0;

    var flagPart1: bool = true;

    for (buffer) |c| {
        if (c < 'a' or c > 'z') break;
        const bitshift: u5 = @intCast(c - 'a');
        const bit = @as(u32, 1) << bitshift;

        if ((count & bit) != 0) {
            while (start < index) {
                const bitshift_temp: u5 = @intCast(buffer[start] - 'a');
                const bit_temp = @as(u32, 1) << bitshift_temp;
                count ^= bit_temp;
                start += 1;
                if (buffer[start - 1] == c) break;
            }
        }
        count |= bit;

        if ((index - start + 1 == 4 and flagPart1) or (index - start + 1 == 14)) {
            std.debug.print("Part {} solution: {}\n", .{ 1 + @as(u32, @intFromBool(!flagPart1)), index + 1 });
            if (flagPart1) {
                flagPart1 = false;
            } else break;
        }
        index += 1;
    }
}
