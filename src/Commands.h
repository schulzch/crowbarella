#ifndef COMMANDS_H
#define COMMANDS_H

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Refactoring.h"
#include <functional>

int replaceMegaMolCalls(
    clang::tooling::RefactoringTool &Tool,
    std::function<int(clang::ast_matchers::MatchFinder *)> RunFinder);

#endif
