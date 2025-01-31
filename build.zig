const std = @import("std");

pub fn build(b: *std.Build) void {
    // create executable
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "bf-interpreter",
        .target = target,
        .optimize = optimize,
    });

    // add source files
    exe.addCSourceFile(.{ .file = b.path("src/main.c") });
    exe.addCSourceFile(.{ .file = b.path("src/error.c") });
    exe.addCSourceFile(.{ .file = b.path("src/file.c") });
    exe.addCSourceFile(.{ .file = b.path("src/bf.c") });

    // add include paths
    exe.addIncludePath(b.path("src"));

    // link against any necessary C libraries
    exe.linkSystemLibrary("c");

    // build the executable
    b.installArtifact(exe);

    // create run option
    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "Run the program.");
    run_step.dependOn(&run_exe.step);

    const clean_step = b.step("clean", "Clean Zig build artifacts.");
    clean_step.dependOn(&b.addRemoveDirTree(b.install_path).step);
    if (@import("builtin").os.tag != .windows) {
        clean_step.dependOn(&b.addRemoveDirTree(b.pathFromRoot("zig-out")).step);
        clean_step.dependOn(&b.addRemoveDirTree(b.pathFromRoot(".zig-cache")).step);
    }
}
