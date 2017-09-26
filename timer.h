#ifndef __TIMER_H__
#define __TIMER_H__

typedef int error_t;

const int success = 0;
const int error_invalid_argument = 1;
const int error_invalid_memory = 2;
const int error_not_implemented = 3;

struct profile_entry;
struct profile;

typedef profile *Profile;
typedef profile_entry *ProfileEntry;

Profile ProfileNew(const char *name, const char *metadata);
error_t ProfileStart(Profile prof);
error_t ProfileEnd(Profile prof);
error_t ProfileDelete(Profile prof);
error_t ProfileReset(Profile prof);
char *ProfileRead(Profile prof);
void ProfileDump(Profile prof);
error_t ProfileAddEntry(Profile prof, ProfileEntry entry);

ProfileEntry ProfileEntryNew(const char *name, const char *metadata);
error_t ProfileEntryStart(ProfileEntry prof);
error_t ProfileEntryEnd(ProfileEntry prof);

#endif // __TIMER_H__
