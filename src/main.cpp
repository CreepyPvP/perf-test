#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <intrin.h>

uint64_t rdtsc(){
    return __rdtsc();
}

static std::vector<int> merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    std::vector<int> res;
    res.reserve(n + m);
    int p1 = 0;
    int p2 = 0;
    while (res.size() < m + n) {
        if (p1 < m && (p2 >= n || nums1[p1] < nums2[p2])) {
            res.push_back(nums1[p1]);
            ++p1;
        } else {
            res.push_back(nums2[p2]);
            ++p2;
        }
    }

    return res;
}

static int* fastmerge(int* nums1, const unsigned int m, int* nums2, const unsigned int n, int* res) {
    unsigned int p1 = 0;
    unsigned int p2 = 0;

    int tmp1;
    int tmp2;
    while (p1 + p2 < m + n) {
        tmp1 = nums1[p1];
        tmp2 = nums2[p2];
        if (p1 < m && (p2 >= n || tmp1 < tmp2)) {
            res[p1 + p2] = tmp1;
            ++p1;
        } else {
            res[p1 + p2] = tmp2;
            ++p2;
        }
    }

    return res;
}

static int* fastmergeLookup(int* nums1, const unsigned int m, int* nums2, const unsigned int n, int* res) {
    unsigned int total = 0;

    int valueLookup[] = {0, 0};
    unsigned int ptrLookup[] = { 0, 0 };
    while (total < m + n) {
        valueLookup[0] = nums1[ptrLookup[0]];
        valueLookup[1] = nums2[ptrLookup[1]];
        bool expr = !(ptrLookup[0] < m && (ptrLookup[1] >= n || valueLookup[0] < valueLookup[1]));
        res[total] = valueLookup[expr];
        ptrLookup[expr] += 1;

        ++total;
    }

    return res;
}

static void check(int* res, unsigned int m, unsigned int n) {
    unsigned int ptr = 0;
    for (unsigned int i = 0; i < (m > n? m : n); ++i) {
        if (i < m) {
            if (res[ptr] != i) {
                printf("error, expected %d, got %d\n", i, res[ptr]);
                return;
            }
            ++ptr;
        }
        
        if (i < n) {
            if (res[ptr] != i) {
                printf("error, expected %d, got %d", i, res[ptr]);
                return;
            }
            ++ptr;
        }
    }
}


int main() {
    // #define TEST
    #ifndef TEST
    const unsigned int iterations = 10000;
    std::vector<int> v1;
    const unsigned int m = 10000;
    int* p1 = (int*) malloc(sizeof(int) * m);
    std::vector<int> v2;
    const unsigned int n = 10000;
    int* p2 = (int*) malloc(sizeof(int) * n);
    int* res = (int*) malloc(sizeof(int) * (m + n));

    uint64_t total = 0, start, end;
    
    for (unsigned int i = 0; i < m; ++i) {
        v1.push_back(i);
        p1[i] = i;
    }
    for (unsigned int i = 0; i < n; ++i) {
        v2.push_back(i);
        p2[i] = i;
        v1.push_back(0);
    }

    for (unsigned int i = 0; i < iterations; ++i) {
        start = rdtsc();
        res = fastmerge(p1, m, p2, n, res);
        end = rdtsc();
        total += (end - start);
    }
    check(res, m, n);
    printf("F: %lu\n", total / iterations);

    total = 0;
    for (unsigned int i = 0; i < iterations; ++i) {
        start = rdtsc();
        merge(v1, m, v2, n);
        end = rdtsc();
        total += (end - start);
    }
    printf("S: %lu\n", total / iterations);

    total = 0;
    for (unsigned int i = 0; i < iterations; ++i) {
        start = rdtsc();
        res = fastmergeLookup(p1, m, p2, n, res);
        end = rdtsc();
        total += (end - start);
    }
    check(res, m, n);
    printf("L: %lu\n", total / iterations);

    total = 0;
    for (unsigned int i = 0; i < iterations; ++i) {
        start = rdtsc();
        res = fastmerge(p1, m, p2, n, res);
        end = rdtsc();
        total += (end - start);
    }
    check(res, m, n);
    printf("F: %lu\n", total / iterations);

    total = 0;
    for (unsigned int i = 0; i < iterations; ++i) {
        start = rdtsc();
        res = fastmergeLookup(p1, m, p2, n, res);
        end = rdtsc();
        total += (end - start);
    }
    check(res, m, n);
    printf("L: %lu\n", total / iterations);
    #else
    int test1[] = { 1, 7, 0 };
    int test2[] = { 4 };
    fastmergeLookup(test1, 2, test2, 1, res);
    #endif
}
