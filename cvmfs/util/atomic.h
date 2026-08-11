/**
 * This file is part of the CernVM File System.
 *
 * Defines wrapper functions for atomic integer operations.  Atomic operations
 * are handled by GCC.
 */

#ifndef CVMFS_UTIL_ATOMIC_H_
#define CVMFS_UTIL_ATOMIC_H_

#include <stdint.h>

#ifdef CVMFS_NAMESPACE_GUARD
namespace CVMFS_NAMESPACE_GUARD {
#endif

typedef int32_t std::atomic<int32_t>;
typedef int64_t std::atomic<int64_t>;

static void inline __attribute__((used)) atomic_init32(std::atomic<int32_t> *a) {
  *a = 0;
}

static void inline __attribute__((used)) atomic_init64(std::atomic<int64_t> *a) {
  *a = 0;
}

static int32_t inline __attribute__((used)) atomic_read32(std::atomic<int32_t> *a) {
  return __sync_fetch_and_add(a, 0);
}

static int64_t inline __attribute__((used)) atomic_read64(std::atomic<int64_t> *a) {
  return __sync_fetch_and_add(a, 0);
}

static void inline __attribute__((used)) atomic_write32(std::atomic<int32_t> *a,
                                                        int32_t value) {
  while (!__sync_bool_compare_and_swap(a, atomic_read32(a), value)) {
  }
}

static void inline __attribute__((used)) atomic_write64(std::atomic<int64_t> *a,
                                                        int64_t value) {
  while (!__sync_bool_compare_and_swap(a, atomic_read64(a), value)) {
  }
}

static void inline __attribute__((used)) atomic_inc32(std::atomic<int32_t> *a) {
  (void)__sync_fetch_and_add(a, 1);
}

static void inline __attribute__((used)) atomic_inc64(std::atomic<int64_t> *a) {
  (void)__sync_fetch_and_add(a, 1);
}

static void inline __attribute__((used)) atomic_dec32(std::atomic<int32_t> *a) {
  (void)__sync_fetch_and_sub(a, 1);
}

static void inline __attribute__((used)) atomic_dec64(std::atomic<int64_t> *a) {
  (void)__sync_fetch_and_sub(a, 1);
}

static int32_t inline __attribute__((used)) atomic_xadd32(std::atomic<int32_t> *a,
                                                          int32_t offset) {
  if (offset < 0)
    return __sync_fetch_and_sub(a, -offset);
  return __sync_fetch_and_add(a, offset);
}

static int64_t inline __attribute__((used)) atomic_xadd64(std::atomic<int64_t> *a,
                                                          int64_t offset) {
  if (offset < 0)
    return __sync_fetch_and_sub(a, -offset);
  return __sync_fetch_and_add(a, offset);
}

static bool inline __attribute__((used)) atomic_cas32(std::atomic<int32_t> *a,
                                                      int32_t cmp,
                                                      int32_t newval) {
  return __sync_bool_compare_and_swap(a, cmp, newval);
}

static bool inline __attribute__((used)) atomic_cas64(std::atomic<int64_t> *a,
                                                      int64_t cmp,
                                                      int64_t newval) {
  // Clang 3.5 has a bug in optimized __sync_bool_compare_and_swap:
  // https://bugs.llvm.org//show_bug.cgi?format=multiple&id=21499
  return __sync_bool_compare_and_swap(a, cmp, newval);
}

static void inline __attribute__((used)) MemoryFence() {
  asm __volatile__("" : : : "memory");
}

#ifdef CVMFS_NAMESPACE_GUARD
}  // namespace CVMFS_NAMESPACE_GUARD
#endif

#endif  // CVMFS_UTIL_ATOMIC_H_
