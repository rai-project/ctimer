
#include <chrono>
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "json.hpp"
#include "timer.h"

#ifdef __GNUC__
#define unused __attribute__((unused))
#else // __GNUC__
#define unused
#endif // __GNUC__

using json = nlohmann::json;

using timestamp_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

static timestamp_t now() { return std::chrono::high_resolution_clock::now(); }

static double elapsed_time(timestamp_t start, timestamp_t end) {
  const auto elapsed =
      std::chrono::duration<double, std::milli>(end - start).count();
  return elapsed;
}

static double to_nanoseconds(timestamp_t t) {
  const auto duration = t.time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

struct profile_entry {
  profile_entry(std::string name) : name_(name) { start(); }
  ~profile_entry() {}

  error_t start() {
    start_ = now();
    return success;
  }

  error_t end() {
    end_ = now();
    return success;
  }

  json to_json() {
    const auto start_ns = to_nanoseconds(start_);
    const auto end_ns = to_nanoseconds(end_);
    return json{
        {"name", name_},
        {"start", start_ns},
        {"end", end_ns},
    };
  }

private:
  std::string name_{};
  timestamp_t start_{}, end_{};
};

struct profile {
  profile() : name_("") { start(); }
  profile(std::string name) : name_(name) { start(); }
  ~profile() { this->reset(); }

  error_t start() {
    start_ = now();
    return success;
  }

  error_t end() {
    end_ = now();
    return success;
  }

  error_t reset() {
    for (auto e : entries_) {
      delete e;
    }
    entries_.clear();
    return success;
  }

  error_t add(profile_entry *entry) {
    entries_.emplace_back(entry);
    return success;
  }

  json to_json() {
    const auto start_ns = to_nanoseconds(start_);
    const auto end_ns = to_nanoseconds(end_);

    json elements = json::array();
    for (const auto e : entries_) {
      elements.emplace_back(e->to_json());
    }
    return json{
        {"name", name_},
        {"start", start_ns},
        {"end", end_ns},
        {"elements", elements},
    };
  }

  std::string read() {
    const auto j = this->to_json();
    return j.dump();
  }

private:
  std::string name_{""};
  std::vector<profile_entry *> entries_{};
  timestamp_t start_{}, end_{};
};

static profile *to_profile(Profile prof) {
  return reinterpret_cast<profile *>(prof);
}

static profile_entry *to_profile_entry(ProfileEntry prof) {
  return reinterpret_cast<profile_entry *>(prof);
}

Profile ProfileNew(const char *name) {
  auto prof = new profile(std::string(name));
  return reinterpret_cast<Profile>(prof);
}

error_t ProfileStart(Profile prof) {
  auto p = to_profile(prof);
  return p->start();
}

error_t ProfileEnd(Profile prof) {
  auto p = to_profile(prof);
  return p->end();
}
error_t ProfileDelete(Profile prof) {
  auto p = to_profile(prof);
  if (p == nullptr) {
    return error_invalid_memory;
  }
  delete p;
  return success;
}

error_t ProfileReset(Profile prof) {
  auto p = to_profile(prof);
  return p->reset();
}
char *ProfileRead(Profile prof) {
  auto p = to_profile(prof);
  const auto s = p->read();
  const auto cstr = s.c_str();
  return strdup(cstr);
}
error_t ProfileAddEntry(Profile prof, ProfileEntry entry) {
  auto p = to_profile(prof);
  auto e = to_profile_entry(entry);
  return p->add(e);
}

ProfileEntry ProfileEntryNew(const char *name) {
  auto entry = new profile_entry(std::string(name));
  return reinterpret_cast<ProfileEntry>(entry);
}

error_t ProfileEntryStart(ProfileEntry prof) {
  auto e = to_profile_entry(prof);
  return e->start();
}
error_t ProfileEntryEnd(ProfileEntry prof) {
  auto e = to_profile_entry(prof);
  return e->end();
}
