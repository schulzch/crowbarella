#ifndef COMMANDS_H
#define COMMANDS_H

#include "clang/Tooling/Refactoring.h"

clang::tooling::FrontendActionFactory *
createReplaceClass(clang::tooling::RefactoringTool &Tool);

#endif
