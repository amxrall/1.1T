#pragma once

// Themida disabled (for x64 / debug / development)

#define CODEREPLACE_START
#define CODEREPLACE_END

#define ENCODE_START
#define ENCODE_END

#define CLEAR_START
#define CLEAR_END

#define VM_START
#define VM_END

#define VM_START_WITHLEVEL(x)

#define UNPROTECTED_START
#define UNPROTECTED_END

#define CHECK_PROTECTION(var, val)
#define CHECK_CODE_INTEGRITY(var, val)
#define CHECK_VIRTUAL_PC(var, val)