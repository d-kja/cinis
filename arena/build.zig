const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "arena",
        .target = target,
        .optimize = optimize,
    });

    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.cpp",
            "src/window.cpp",
            "src/background.cpp",
            "src/character.cpp",
            "src/game.cpp",
        },
        .flags = &.{"-std=c++17"},
    });

    exe.linkLibCpp();
    exe.linkSystemLibrary("raylib");

    exe.addIncludePath(b.path("src"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run executable");
    run_step.dependOn(&run_cmd.step);
}
