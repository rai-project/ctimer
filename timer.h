#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
#define EXTERN_C extern "C"
#endif // __cplusplus

typedef int error_t;

const int success = 0;
const int error_invalid_argument = 1;
const int error_invalid_memory = 2;
const int error_not_implemented = 3;

struct profile_entry;
struct profile;

typedef profile *Profile;
typedef profile_entry *ProfileEntry;

EXTERN_C Profile ProfileNew(const char *name, const char *metadata);
EXTERN_C error_t ProfileStart(Profile prof);
EXTERN_C error_t ProfileEnd(Profile prof);
EXTERN_C error_t ProfileDelete(Profile prof);
EXTERN_C error_t ProfileReset(Profile prof);
EXTERN_C char *ProfileRead(Profile prof);
EXTERN_C void ProfileDump(Profile prof);
EXTERN_C error_t ProfileAddEntry(Profile prof, ProfileEntry entry);

EXTERN_C ProfileEntry ProfileEntryNew(const char *name, const char *metadata);
EXTERN_C error_t ProfileEntryStart(ProfileEntry prof);
EXTERN_C error_t ProfileEntryEnd(ProfileEntry prof);

#endif // __TIMER_H__
