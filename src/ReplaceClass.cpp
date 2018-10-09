#include "Commands.h"

using namespace clang;
using namespace llvm;

tooling::FrontendActionFactory *
createReplaceClass(tooling::RefactoringTool &Tool) {
  // XXX: not yet ready to share with other people.
  return nullptr;
}
