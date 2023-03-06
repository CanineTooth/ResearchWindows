#pragma once
#include <intrin.h>

typedef struct _cpuid_regs
{
	unsigned long eax;
	unsigned long ebx;
	unsigned long ecx;
	unsigned long edx;
}cpuid_regs, * pcpuid_regs;

/* cpuid_features bits */
#define CPUID_FP87 (1U << 0)
#define CPUID_VME  (1U << 1)
#define CPUID_DE   (1U << 2)
#define CPUID_PSE  (1U << 3)
#define CPUID_TSC  (1U << 4)
#define CPUID_MSR  (1U << 5)
#define CPUID_PAE  (1U << 6)
#define CPUID_MCE  (1U << 7)
#define CPUID_CX8  (1U << 8)
#define CPUID_APIC (1U << 9)
#define CPUID_SEP  (1U << 11) /* sysenter/sysexit */
#define CPUID_MTRR (1U << 12)
#define CPUID_PGE  (1U << 13)
#define CPUID_MCA  (1U << 14)
#define CPUID_CMOV (1U << 15)
#define CPUID_PAT  (1U << 16)
#define CPUID_PSE36   (1U << 17)
#define CPUID_PN   (1U << 18)
#define CPUID_CLFLUSH (1U << 19)
#define CPUID_DTS (1U << 21)
#define CPUID_ACPI (1U << 22)
#define CPUID_MMX  (1U << 23)
#define CPUID_FXSR (1U << 24)
#define CPUID_SSE  (1U << 25)
#define CPUID_SSE2 (1U << 26)
#define CPUID_SS (1U << 27)
#define CPUID_HT (1U << 28)
#define CPUID_TM (1U << 29)
#define CPUID_IA64 (1U << 30)
#define CPUID_PBE (1U << 31)

#define CPUID_EXT_SSE3     (1U << 0)
#define CPUID_EXT_PCLMULQDQ (1U << 1)
#define CPUID_EXT_DTES64   (1U << 2)
#define CPUID_EXT_MONITOR  (1U << 3)
#define CPUID_EXT_DSCPL    (1U << 4)
#define CPUID_EXT_VMX      (1U << 5)
#define CPUID_EXT_SMX      (1U << 6)
#define CPUID_EXT_EST      (1U << 7)
#define CPUID_EXT_TM2      (1U << 8)
#define CPUID_EXT_SSSE3    (1U << 9)
#define CPUID_EXT_CID      (1U << 10)
#define CPUID_EXT_FMA      (1U << 12)
#define CPUID_EXT_CX16     (1U << 13)
#define CPUID_EXT_XTPR     (1U << 14)
#define CPUID_EXT_PDCM     (1U << 15)
#define CPUID_EXT_PCID     (1U << 17)
#define CPUID_EXT_DCA      (1U << 18)
#define CPUID_EXT_SSE41    (1U << 19)
#define CPUID_EXT_SSE42    (1U << 20)
#define CPUID_EXT_X2APIC   (1U << 21)
#define CPUID_EXT_MOVBE    (1U << 22)
#define CPUID_EXT_POPCNT   (1U << 23)
#define CPUID_EXT_TSC_DEADLINE_TIMER (1U << 24)
#define CPUID_EXT_AES      (1U << 25)
#define CPUID_EXT_XSAVE    (1U << 26)
#define CPUID_EXT_OSXSAVE  (1U << 27)
#define CPUID_EXT_AVX      (1U << 28)
#define CPUID_EXT_F16C     (1U << 29)
#define CPUID_EXT_RDRAND   (1U << 30)
#define CPUID_EXT_HYPERVISOR  (1U << 31)

#define CPUID_EXT2_FPU     (1U << 0)
#define CPUID_EXT2_VME     (1U << 1)
#define CPUID_EXT2_DE      (1U << 2)
#define CPUID_EXT2_PSE     (1U << 3)
#define CPUID_EXT2_TSC     (1U << 4)
#define CPUID_EXT2_MSR     (1U << 5)
#define CPUID_EXT2_PAE     (1U << 6)
#define CPUID_EXT2_MCE     (1U << 7)
#define CPUID_EXT2_CX8     (1U << 8)
#define CPUID_EXT2_APIC    (1U << 9)
#define CPUID_EXT2_SYSCALL (1U << 11)
#define CPUID_EXT2_MTRR    (1U << 12)
#define CPUID_EXT2_PGE     (1U << 13)
#define CPUID_EXT2_MCA     (1U << 14)
#define CPUID_EXT2_CMOV    (1U << 15)
#define CPUID_EXT2_PAT     (1U << 16)
#define CPUID_EXT2_PSE36   (1U << 17)
#define CPUID_EXT2_MP      (1U << 19)
#define CPUID_EXT2_NX      (1U << 20)
#define CPUID_EXT2_MMXEXT  (1U << 22)
#define CPUID_EXT2_MMX     (1U << 23)
#define CPUID_EXT2_FXSR    (1U << 24)
#define CPUID_EXT2_FFXSR   (1U << 25)
#define CPUID_EXT2_PDPE1GB (1U << 26)
#define CPUID_EXT2_RDTSCP  (1U << 27)
#define CPUID_EXT2_LM      (1U << 29)
#define CPUID_EXT2_3DNOWEXT (1U << 30)
#define CPUID_EXT2_3DNOW   (1U << 31)

/* CPUID[8000_0001].EDX bits that are aliase of CPUID[1].EDX bits on AMD CPUs */
#define CPUID_EXT2_AMD_ALIASES (CPUID_EXT2_FPU | CPUID_EXT2_VME | \
                                CPUID_EXT2_DE | CPUID_EXT2_PSE | \
                                CPUID_EXT2_TSC | CPUID_EXT2_MSR | \
                                CPUID_EXT2_PAE | CPUID_EXT2_MCE | \
                                CPUID_EXT2_CX8 | CPUID_EXT2_APIC | \
                                CPUID_EXT2_MTRR | CPUID_EXT2_PGE | \
                                CPUID_EXT2_MCA | CPUID_EXT2_CMOV | \
                                CPUID_EXT2_PAT | CPUID_EXT2_PSE36 | \
                                CPUID_EXT2_MMX | CPUID_EXT2_FXSR)

#define CPUID_EXT3_LAHF_LM (1U << 0)
#define CPUID_EXT3_CMP_LEG (1U << 1)
#define CPUID_EXT3_SVM     (1U << 2)
#define CPUID_EXT3_EXTAPIC (1U << 3)
#define CPUID_EXT3_CR8LEG  (1U << 4)
#define CPUID_EXT3_ABM     (1U << 5)
#define CPUID_EXT3_SSE4A   (1U << 6)
#define CPUID_EXT3_MISALIGNSSE (1U << 7)
#define CPUID_EXT3_3DNOWPREFETCH (1U << 8)
#define CPUID_EXT3_OSVW    (1U << 9)
#define CPUID_EXT3_IBS     (1U << 10)
#define CPUID_EXT3_XOP     (1U << 11)
#define CPUID_EXT3_SKINIT  (1U << 12)
#define CPUID_EXT3_WDT     (1U << 13)
#define CPUID_EXT3_LWP     (1U << 15)
#define CPUID_EXT3_FMA4    (1U << 16)
#define CPUID_EXT3_TCE     (1U << 17)
#define CPUID_EXT3_NODEID  (1U << 19)
#define CPUID_EXT3_TBM     (1U << 21)
#define CPUID_EXT3_TOPOEXT (1U << 22)
#define CPUID_EXT3_PERFCORE (1U << 23)
#define CPUID_EXT3_PERFNB  (1U << 24)

#define CPUID_SVM_NPT             (1U << 0)
#define CPUID_SVM_LBRV            (1U << 1)
#define CPUID_SVM_SVMLOCK         (1U << 2)
#define CPUID_SVM_NRIPSAVE        (1U << 3)
#define CPUID_SVM_TSCSCALE        (1U << 4)
#define CPUID_SVM_VMCBCLEAN       (1U << 5)
#define CPUID_SVM_FLUSHASID       (1U << 6)
#define CPUID_SVM_DECODEASSIST    (1U << 7)
#define CPUID_SVM_PAUSEFILTER     (1U << 10)
#define CPUID_SVM_PFTHRESHOLD     (1U << 12)
#define CPUID_SVM_AVIC            (1U << 13)
#define CPUID_SVM_V_VMSAVE_VMLOAD (1U << 15)
#define CPUID_SVM_VGIF            (1U << 16)
#define CPUID_SVM_SVME_ADDR_CHK   (1U << 28)

/* Support RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE */
#define CPUID_7_0_EBX_FSGSBASE          (1U << 0)
/* Support SGX */
#define CPUID_7_0_EBX_SGX               (1U << 2)
/* 1st Group of Advanced Bit Manipulation Extensions */
#define CPUID_7_0_EBX_BMI1              (1U << 3)
/* Hardware Lock Elision */
#define CPUID_7_0_EBX_HLE               (1U << 4)
/* Intel Advanced Vector Extensions 2 */
#define CPUID_7_0_EBX_AVX2              (1U << 5)
/* Supervisor-mode Execution Prevention */
#define CPUID_7_0_EBX_SMEP              (1U << 7)
/* 2nd Group of Advanced Bit Manipulation Extensions */
#define CPUID_7_0_EBX_BMI2              (1U << 8)
/* Enhanced REP MOVSB/STOSB */
#define CPUID_7_0_EBX_ERMS              (1U << 9)
/* Invalidate Process-Context Identifier */
#define CPUID_7_0_EBX_INVPCID           (1U << 10)
/* Restricted Transactional Memory */
#define CPUID_7_0_EBX_RTM               (1U << 11)
/* Memory Protection Extension */
#define CPUID_7_0_EBX_MPX               (1U << 14)
/* AVX-512 Foundation */
#define CPUID_7_0_EBX_AVX512F           (1U << 16)
/* AVX-512 Doubleword & Quadword Instruction */
#define CPUID_7_0_EBX_AVX512DQ          (1U << 17)
/* Read Random SEED */
#define CPUID_7_0_EBX_RDSEED            (1U << 18)
/* ADCX and ADOX instructions */
#define CPUID_7_0_EBX_ADX               (1U << 19)
/* Supervisor Mode Access Prevention */
#define CPUID_7_0_EBX_SMAP              (1U << 20)
/* AVX-512 Integer Fused Multiply Add */
#define CPUID_7_0_EBX_AVX512IFMA        (1U << 21)
/* Persistent Commit */
#define CPUID_7_0_EBX_PCOMMIT           (1U << 22)
/* Flush a Cache Line Optimized */
#define CPUID_7_0_EBX_CLFLUSHOPT        (1U << 23)
/* Cache Line Write Back */
#define CPUID_7_0_EBX_CLWB              (1U << 24)
/* Intel Processor Trace */
#define CPUID_7_0_EBX_INTEL_PT          (1U << 25)
/* AVX-512 Prefetch */
#define CPUID_7_0_EBX_AVX512PF          (1U << 26)
/* AVX-512 Exponential and Reciprocal */
#define CPUID_7_0_EBX_AVX512ER          (1U << 27)
/* AVX-512 Conflict Detection */
#define CPUID_7_0_EBX_AVX512CD          (1U << 28)
/* SHA1/SHA256 Instruction Extensions */
#define CPUID_7_0_EBX_SHA_NI            (1U << 29)
/* AVX-512 Byte and Word Instructions */
#define CPUID_7_0_EBX_AVX512BW          (1U << 30)
/* AVX-512 Vector Length Extensions */
#define CPUID_7_0_EBX_AVX512VL          (1U << 31)

/* AVX-512 Vector Byte Manipulation Instruction */
#define CPUID_7_0_ECX_AVX512_VBMI       (1U << 1)
/* User-Mode Instruction Prevention */
#define CPUID_7_0_ECX_UMIP              (1U << 2)
/* Protection Keys for User-mode Pages */
#define CPUID_7_0_ECX_PKU               (1U << 3)
/* OS Enable Protection Keys */
#define CPUID_7_0_ECX_OSPKE             (1U << 4)
/* UMONITOR/UMWAIT/TPAUSE Instructions */
#define CPUID_7_0_ECX_WAITPKG           (1U << 5)
/* Additional AVX-512 Vector Byte Manipulation Instruction */
#define CPUID_7_0_ECX_AVX512_VBMI2      (1U << 6)
/* Galois Field New Instructions */
#define CPUID_7_0_ECX_GFNI              (1U << 8)
/* Vector AES Instructions */
#define CPUID_7_0_ECX_VAES              (1U << 9)
/* Carry-Less Multiplication Quadword */
#define CPUID_7_0_ECX_VPCLMULQDQ        (1U << 10)
/* Vector Neural Network Instructions */
#define CPUID_7_0_ECX_AVX512VNNI        (1U << 11)
/* Support for VPOPCNT[B,W] and VPSHUFBITQMB */
#define CPUID_7_0_ECX_AVX512BITALG      (1U << 12)
/* POPCNT for vectors of DW/QW */
#define CPUID_7_0_ECX_AVX512_VPOPCNTDQ  (1U << 14)
/* 5-level Page Tables */
#define CPUID_7_0_ECX_LA57              (1U << 16)
/* Read Processor ID */
#define CPUID_7_0_ECX_RDPID             (1U << 22)
/* Bus Lock Debug Exception */
#define CPUID_7_0_ECX_BUS_LOCK_DETECT   (1U << 24)
/* Cache Line Demote Instruction */
#define CPUID_7_0_ECX_CLDEMOTE          (1U << 25)
/* Move Doubleword as Direct Store Instruction */
#define CPUID_7_0_ECX_MOVDIRI           (1U << 27)
/* Move 64 Bytes as Direct Store Instruction */
#define CPUID_7_0_ECX_MOVDIR64B         (1U << 28)
/* Support SGX Launch Control */
#define CPUID_7_0_ECX_SGX_LC            (1U << 30)
/* Protection Keys for Supervisor-mode Pages */
#define CPUID_7_0_ECX_PKS               (1U << 31)

/* AVX512 Neural Network Instructions */
#define CPUID_7_0_EDX_AVX512_4VNNIW     (1U << 2)
/* AVX512 Multiply Accumulation Single Precision */
#define CPUID_7_0_EDX_AVX512_4FMAPS     (1U << 3)
/* Fast Short Rep Mov */
#define CPUID_7_0_EDX_FSRM              (1U << 4)
/* AVX512 Vector Pair Intersection to a Pair of Mask Registers */
#define CPUID_7_0_EDX_AVX512_VP2INTERSECT (1U << 8)
/* SERIALIZE instruction */
#define CPUID_7_0_EDX_SERIALIZE         (1U << 14)
/* TSX Suspend Load Address Tracking instruction */
#define CPUID_7_0_EDX_TSX_LDTRK         (1U << 16)
/* Architectural LBRs */
#define CPUID_7_0_EDX_ARCH_LBR          (1U << 19)
/* AVX512_FP16 instruction */
#define CPUID_7_0_EDX_AVX512_FP16       (1U << 23)
/* AMX tile (two-dimensional register) */
#define CPUID_7_0_EDX_AMX_TILE          (1U << 24)
/* Speculation Control */
#define CPUID_7_0_EDX_SPEC_CTRL         (1U << 26)
/* Single Thread Indirect Branch Predictors */
#define CPUID_7_0_EDX_STIBP             (1U << 27)
/* Arch Capabilities */
#define CPUID_7_0_EDX_ARCH_CAPABILITIES (1U << 29)
/* Core Capability */
#define CPUID_7_0_EDX_CORE_CAPABILITY   (1U << 30)
/* Speculative Store Bypass Disable */
#define CPUID_7_0_EDX_SPEC_CTRL_SSBD    (1U << 31)

/* AVX VNNI Instruction */
#define CPUID_7_1_EAX_AVX_VNNI          (1U << 4)
/* AVX512 BFloat16 Instruction */
#define CPUID_7_1_EAX_AVX512_BF16       (1U << 5)
/* XFD Extend Feature Disabled */
#define CPUID_D_1_EAX_XFD               (1U << 4)

// Intel Processor Trace Capabilities
/* CR3 Filtering Support  */
#define CPUID_14_0_EBX_CR3_FILTERING    (1U << 0)
/* Configurable PSB and Cycle-Accurate Mode Supported */
#define CPUID_14_0_EBX_PSB_CYCAL        (1U << 1)
/* IP Filtering and TraceStop supported, and Preserve Intel PT MSRs across warm reset */
#define CPUID_14_0_EBX_IP_FILTERING     (1U << 2)
/* MTC Supported */
#define CPUID_14_0_EBX_MTC              (1U << 3)
/* PTWRITE Supported */
#define CPUID_14_0_EBX_PTWRITE          (1U << 4)
/* Power Event Trace Supported */
#define CPUID_14_0_EBX_PE_TRACE         (1U << 5)
/* PSB and PMI Preservation Supported */
#define CPUID_14_0_EBX_PSB_PMI_PRE      (1U << 6)
/* Event Trace Supported */
#define CPUID_14_0_EBX_EVENT_TRACE      (1U << 7)
/* TNT Disable Supported */
#define CPUID_14_0_EBX_TNT_CONTROL      (1U << 8)

/* ToPA Output Supported */
#define CPUID_14_0_ECX_TOPA_OUTPUT      (1U << 0)
/* ToPA Tables Allow Multiple Output Entries */
#define CPUID_14_0_ECX_TOPA_MULTI_ENTRY (1U << 1)
/* Single-Range Output Supported */
#define CPUID_14_0_ECX_SINGLE_OUTPUT    (1U << 2)
/* Output to Trace Transport Subsystem Supported */
#define CPUID_14_0_ECX_TRACE_SUBSYSTEM  (1U << 3)
/* Packets which contain IP payload have LIP values */
#define CPUID_14_0_ECX_LIP              (1U << 31)

/* CLZERO instruction */
#define CPUID_8000_0008_EBX_CLZERO      (1U << 0)
/* Always save/restore FP error pointers */
#define CPUID_8000_0008_EBX_XSAVEERPTR  (1U << 2)
/* Write back and do not invalidate cache */
#define CPUID_8000_0008_EBX_WBNOINVD    (1U << 9)
/* Indirect Branch Prediction Barrier */
#define CPUID_8000_0008_EBX_IBPB        (1U << 12)
/* Indirect Branch Restricted Speculation */
#define CPUID_8000_0008_EBX_IBRS        (1U << 14)
/* Single Thread Indirect Branch Predictors */
#define CPUID_8000_0008_EBX_STIBP       (1U << 15)
/* Speculative Store Bypass Disable */
#define CPUID_8000_0008_EBX_AMD_SSBD    (1U << 24)

#define CPUID_XSAVE_XSAVEOPT   (1U << 0)
#define CPUID_XSAVE_XSAVEC     (1U << 1)
#define CPUID_XSAVE_XGETBV1    (1U << 2)
#define CPUID_XSAVE_XSAVES     (1U << 3)

#define CPUID_6_EAX_ARAT       (1U << 2)

/* CPUID[0x80000007].EDX flags: */
#define CPUID_APM_INVTSC       (1U << 8)

#define CPUID_VENDOR_SZ      12

#define CPUID_VENDOR_INTEL_1 0x756e6547 /* "Genu" */
#define CPUID_VENDOR_INTEL_2 0x49656e69 /* "ineI" */
#define CPUID_VENDOR_INTEL_3 0x6c65746e /* "ntel" */
#define CPUID_VENDOR_INTEL "GenuineIntel"

#define CPUID_VENDOR_AMD_1   0x68747541 /* "Auth" */
#define CPUID_VENDOR_AMD_2   0x69746e65 /* "enti" */
#define CPUID_VENDOR_AMD_3   0x444d4163 /* "cAMD" */
#define CPUID_VENDOR_AMD   "AuthenticAMD"

static inline void native_cpuid(unsigned int* eax, unsigned int* ebx, unsigned int* ecx, unsigned int* edx)
{
	cpuid_regs regs = { *eax,*ebx,*ecx,*edx };
	__cpuidex((int*)&regs, regs.eax, regs.ecx);
	*eax = regs.eax;
	*ebx = regs.ebx;
	*ecx = regs.ecx;
	*edx = regs.edx;
}

/*
 * Generic CPUID function
 * clear %ecx since some cpus (Cyrix MII) do not set or clear %ecx
 * resulting in stale register contents being returned.
 */
static inline void cpuid(unsigned int op,
	unsigned int* eax, unsigned int* ebx,
	unsigned int* ecx, unsigned int* edx)
{
	*eax = op;
	*ecx = 0;
	native_cpuid(eax, ebx, ecx, edx);
}

/* Some CPUID calls want 'subleaf' to be placed in ecx */
static inline void cpuid_subleaf(unsigned int op, int count,
	unsigned int* eax, unsigned int* ebx,
	unsigned int* ecx, unsigned int* edx)
{
	*eax = op;
	*ecx = count;
	native_cpuid(eax, ebx, ecx, edx);
}

/*
 * CPUID functions returning a single datum
 */
static inline unsigned int cpuid_eax(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;
	cpuid(op, &eax, &ebx, &ecx, &edx);
	return eax;
}

static inline unsigned int cpuid_ebx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;
	cpuid(op, &eax, &ebx, &ecx, &edx);
	return ebx;
}

static inline unsigned int cpuid_ecx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;
	cpuid(op, &eax, &ebx, &ecx, &edx);
	return ecx;
}

static inline unsigned int cpuid_edx(unsigned int op)
{
	unsigned int eax, ebx, ecx, edx;
	cpuid(op, &eax, &ebx, &ecx, &edx);
	return edx;
}

static inline bool cpu_is_intel()
{
	bool result = false;
	cpuid_regs regs = { 0 };
	__cpuidex((int*)&regs, regs.eax, regs.ecx);
	if (regs.ebx == CPUID_VENDOR_INTEL_1 &&
		regs.edx == CPUID_VENDOR_INTEL_2 &&
		regs.ecx == CPUID_VENDOR_INTEL_3)
	{
		result = true;
	}
	return result;
}

static inline bool cpu_is_amd()
{
	bool result = false;
	cpuid_regs regs = { 0 };
	__cpuidex((int*)&regs, regs.eax, regs.ecx);
	if (regs.ebx == CPUID_VENDOR_AMD_1 &&
		regs.edx == CPUID_VENDOR_AMD_2 &&
		regs.ecx == CPUID_VENDOR_AMD_3)
	{
		result = true;
	}
	return result;
}

static inline bool cpu_has_vmx()
{
	bool result = false;
	// CheckVirtualStatus Hyper-V
	if ((int)cpuid_ecx(1u) < 0)
	{
		return true;
	}
	// CheckVirtualStatus INTEL
	if (cpu_is_intel())
	{
		result = cpuid_ecx(1u) & CPUID_EXT_VMX;
	}
	// CheckVirtualStatus AMD
	if (cpu_is_amd())
	{
		result = cpuid_ecx(0x80000001) & CPUID_EXT3_SVM;
	}
	return result;
}

static inline bool cpu_has_intel_pt()
{
	bool result = false;
	if (cpu_is_intel())
	{
		result = cpuid_ebx(7u) & CPUID_7_0_EBX_INTEL_PT;
	}
	return result;
}