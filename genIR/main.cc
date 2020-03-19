#include "clang/Lex/Preprocessor.h"
#include <clang/Basic/TargetInfo.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticBuffer.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <llvm/Bitstream/BitstreamWriter.h>
// #include <llvm/Bitstream/ReaderWriter.h>
#include <llvm/Linker/Linker.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

//#include <llvm/PassManager.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/TargetSelect.h>

#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#include <llvm/IR/DataLayout.h>

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// const char *program_h = "#define TEST_C 21\n";

const char *program_src = "int main() \n"
                          "{\n"
                          "  int i;\n"
                          "  i = 10;\n"
                          "  return i;\n"
                          "}\n";

static llvm::LLVMContext TheContext;

int main() {

  clang::CompilerInstance c;
  clang::EmitLLVMOnlyAction act(&TheContext);

  std::string log;
  llvm::raw_string_ostream s_log(log);

  // compiler options:
  std::vector<std::string> opts_array;

  opts_array.push_back("input.c");

  opts_array.push_back("-v");

  std::vector<const char *> opts_carray;
  for (unsigned i = 0; i < opts_array.size(); i++) {
    opts_carray.push_back(opts_array.at(i).c_str());
  }

  llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagID;
  llvm::IntrusiveRefCntPtr<clang::DiagnosticOptions> DiagOpts;
  clang::TextDiagnosticBuffer *DiagsBuffer;

  DiagID = new clang::DiagnosticIDs();
  DiagOpts = new clang::DiagnosticOptions();
  DiagsBuffer = new clang::TextDiagnosticBuffer();

  clang::DiagnosticsEngine Diags(DiagID, &*DiagOpts, DiagsBuffer);
  bool Success;

  Success = clang::CompilerInvocation::CreateFromArgs(c.getInvocation(),
                                                      opts_carray, Diags);
  if (!Success) {
    std::cerr << "invalide option" << std::endl;
    return 1;
  }

  c.getFrontendOpts().ProgramAction = clang::frontend::EmitLLVMOnly;

  c.getHeaderSearchOpts().UseBuiltinIncludes = true;
  c.getHeaderSearchOpts().UseStandardSystemIncludes = true;

  c.getLangOpts().NoBuiltin = true;
  // c.getTargetOpts().Triple = triple;
  // c.getTargetOpts().CPU = processor;
  clang::InputKind ik(clang::Language::C);
  llvm::Triple tr("x86_64", "AMD", "Linux");
  c.getInvocation().setLangDefaults(c.getLangOpts(), ik, tr,
                                    c.getPreprocessorOpts(),
                                    clang::LangStandard::lang_gnu99);
  c.createDiagnostics(
      new clang::TextDiagnosticPrinter(s_log, &c.getDiagnosticOpts()));

  c.getPreprocessorOpts().addRemappedFile(
      "input.c", llvm::MemoryBuffer::getMemBuffer(program_src).get());
  c.getFrontendOpts().ShowStats = 1;

  // 			c.createFileManager();
  // 			auto &fm = c.getFileManager();
  // 			c.createSourceManager(fm);
  // 			auto &sm = c.getSourceManager();

  // llvm::MemoryBuffer *buffer =
  //    llvm::MemoryBuffer::getMemBuffer(program_h, "inc.h");
  // c.getPreprocessorOpts().addRemappedFile("inc.h", buffer);

  // c.createPreprocessor()

  // Compile the code
  if (!c.ExecuteAction(act)) {
    printf("failed to compile\n");
    printf("%s", log.c_str());
    return 2;
  }

  act.takeModule();
  return 0;
}
