/* compile 
clang++ compile.cc -o main -L/usr/local/lib  -I/usr/local/include -std=c++14   -fno-exceptions -fno-rtti -D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -I/home/jatin/github/llvm-project/clang/lib/CodeGen -lLLVMXRay -lLLVMWindowsManifest -lLLVMTableGen -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMOrcJIT -lLLVMOrcError -lLLVMJITLink -lLLVMObjectYAML -lLLVMMCA -lLLVMLTO -lLLVMPasses -lLLVMCoroutines -lLLVMObjCARCOpts -lLLVMLineEditor -lLLVMLibDriver -lLLVMInterpreter -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMDWARFLinker -lLLVMDlltoolDriver -lLLVMOption -lLLVMDebugInfoGSYM -lLLVMCoverage -lLLVMXCoreDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Utils -lLLVMX86Info -lLLVMWebAssemblyDisassembler -lLLVMWebAssemblyCodeGen -lLLVMWebAssemblyDesc -lLLVMWebAssemblyAsmParser -lLLVMWebAssemblyInfo -lLLVMSystemZDisassembler -lLLVMSystemZCodeGen -lLLVMSystemZAsmParser -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSparcDisassembler -lLLVMSparcCodeGen -lLLVMSparcAsmParser -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMRISCVDisassembler -lLLVMRISCVCodeGen -lLLVMRISCVAsmParser -lLLVMRISCVDesc -lLLVMRISCVUtils -lLLVMRISCVInfo -lLLVMPowerPCDisassembler -lLLVMPowerPCCodeGen -lLLVMPowerPCAsmParser -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo -lLLVMMSP430Disassembler -lLLVMMSP430CodeGen -lLLVMMSP430AsmParser -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMipsDisassembler -lLLVMMipsCodeGen -lLLVMMipsAsmParser -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMLanaiDisassembler -lLLVMLanaiCodeGen -lLLVMLanaiAsmParser -lLLVMLanaiDesc -lLLVMLanaiInfo -lLLVMHexagonDisassembler -lLLVMHexagonCodeGen -lLLVMHexagonAsmParser -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMBPFDisassembler -lLLVMBPFCodeGen -lLLVMBPFAsmParser -lLLVMBPFDesc -lLLVMBPFInfo -lLLVMARMDisassembler -lLLVMARMCodeGen -lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMUtils -lLLVMARMInfo -lLLVMAMDGPUDisassembler -lLLVMAMDGPUCodeGen -lLLVMMIRParser -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader -lLLVMAsmParser -lLLVMFrontendOpenMP -lLLVMAMDGPUAsmParser -lLLVMAMDGPUDesc -lLLVMAMDGPUUtils -lLLVMAMDGPUInfo -lLLVMAArch64Disassembler -lLLVMMCDisassembler -lLLVMAArch64CodeGen -lLLVMCFGuard -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMObject -lLLVMTextAPI -lLLVMBitReader -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMAArch64AsmParser -lLLVMMCParser -lLLVMAArch64Desc -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBinaryFormat -lLLVMAArch64Utils -lLLVMAArch64Info -lLLVMSupport -lLLVMDemangle -lclang -lclangIndex -lclangFrontend -lclangDriver -lclangSerialization -lclangParse -lclangSema -lclangAnalysis -lclangAST -lclangLex -lclangBasic -ldl -lpthread -ltinfo -lLLVMSupport -lz -lLLVMMC -lLLVMMCA -lclangTooling -lclangEdit -lclangCodeGen -fuse-ld=lld -g
*/


#include <string>
#include <vector>

#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/TargetInfo.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>

using namespace std;
using namespace clang;
using namespace llvm;

int main() {

    constexpr auto testCodeFileName = "test.cpp";
    constexpr auto testCode = "int test() { return 2+2; }";

    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();

    // Prepare compilation arguments
    vector<const char *> args;
    args.push_back(testCodeFileName);

    // Prepare DiagnosticEngine 
    DiagnosticOptions DiagOpts;
    TextDiagnosticPrinter *textDiagPrinter =
            new clang::TextDiagnosticPrinter(errs(),
                                         &DiagOpts);
    IntrusiveRefCntPtr<clang::DiagnosticIDs> pDiagIDs;
    DiagnosticsEngine *pDiagnosticsEngine =
            new DiagnosticsEngine(pDiagIDs,
                                         &DiagOpts,
                                         textDiagPrinter);

    // Initialize CompilerInvocation
    CompilerInvocation *CI = new CompilerInvocation();
    ArrayRef<const char *> aref(args.data(), args.data() + args.size());
    CompilerInvocation::CreateFromArgs(*CI, aref, *pDiagnosticsEngine);

    // Map code filename to a memoryBuffer
    StringRef testCodeData(testCode);
    unique_ptr<MemoryBuffer> buffer = MemoryBuffer::getMemBufferCopy(testCodeData);
    CI->getPreprocessorOpts().addRemappedFile(testCodeFileName, buffer.get());


    // Create and initialize CompilerInstance
    CompilerInstance Clang;
    std::shared_ptr<CompilerInvocation> ciptr(CI);
    Clang.setInvocation(ciptr);
    Clang.createDiagnostics();

    // Set target (I guess I can initialize only the BPF target, but I don't know how)
    InitializeAllTargets();
    const std::shared_ptr<clang::TargetOptions> targetOptions = std::make_shared<clang::TargetOptions>();
    targetOptions->Triple = string("bpf");
    TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(*pDiagnosticsEngine,targetOptions);
    Clang.setTarget(pTargetInfo);

    // Create and execute action
    // CodeGenAction *compilerAction = new EmitLLVMOnlyAction();
    CodeGenAction *compilerAction = new EmitAssemblyAction();
    Clang.ExecuteAction(*compilerAction);
    auto module = compilerAction->takeModule();
    module->dump();

    buffer.release();
}