// RUN: %clang_profgen -o %t -O3 %s
// RUN: env LLVM_PROFILE_FILE=%h.%t-%h.profraw_%h %run %t
// RUN: llvm-profdata merge -o %t.profdata `uname -n`.%t-`uname -n`.profraw_`uname -n`
// RUN: %clang_profuse=%t.profdata -o - -S -emit-llvm %s | FileCheck %s
// REQUIRES: shell

int main(int argc, const char *argv[]) {
  // CHECK: br i1 %{{.*}}, label %{{.*}}, label %{{.*}}, !prof ![[PD1:[0-9]+]]
  if (argc > 2)
    return 1;
  return 0;
}
// CHECK: ![[PD1]] = !{!"branch_weights", i32 1, i32 2}
