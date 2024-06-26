// Ֆակտորիալ

double rec_fact(unsigned n)
{
    return n == 0 ? 1.0 : n * rec_fact(n - 1);
}

double tcr_fact(unsigned n, double fact = 1.0)
{
    return n == 0 ? fact : tcr_fact(n - 1, n * fact);
}

double tcr_fact_caller(unsigned n)
{
    return tcr_fact(n);
}

double itr_fact_0(unsigned n)
{
    double fact = 1.0;
    while (true)
    {
        if (n == 0)
            return fact;

        const auto old_n = n;
        const auto old_fact = fact;

        n = old_n - 1;
        fact = old_n * old_fact;
    }
}

double itr_fact(unsigned n)
{
    double fact = 1.0;
    for (; n != 0; --n)
        fact *= n;
    return fact;
}


typedef double (*fact_variant)(unsigned);
int test_fact(fact_variant fact)
{
    const unsigned ns[] = { 0, 1, 2, 5, 7, 10 };
    const double fs[] = { 1., 1., 2., 120., 5040., 3628800. };
    for (unsigned i = 0; i < sizeof(fs) / sizeof(double); ++i)
        if (fact(ns[i]) != fs[i])
            return i + 1;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Ֆիբոնաչի

double rec_fib(unsigned n)
{
    return n < 2 ? n : rec_fib(n - 1) + rec_fib(n - 2);
}

double tcr_fib(unsigned n, double a = 0.0, double b = 1.0)
{
    return n == 0 ? a : tcr_fib(n - 1, b, a + b);
}

double tcr_fib_caller(unsigned n)
{
    return tcr_fib(n);
}

double itr_fib_0(unsigned n)
{
    double a = 0.0, b = 1.0;
    while (true)
    {
        if (n == 0)
            return a;

        const auto old_n = n;
        const auto old_a = a, old_b = b;

        a = old_b;
        b = old_a + old_b;
        n = old_n - 1;
    }
}

double itr_fib(unsigned n)
{
    double a = 0.0, b = 1.0;
    while (n-- > 0)
    {
        const auto sum = a + b;
        a = b;
        b = sum;
    }

    return a;
}


typedef double(*fib_variant)(unsigned);
int test_fib(fib_variant fact)
{
    const unsigned ns[] = { 0, 1, 2, 4, 6, 10 };
    const double fs[] = { 0., 1., 1., 3., 8., 55. };
    for (unsigned i = 0; i < sizeof(fs) / sizeof(double); ++i)
        if (fact(ns[i]) != fs[i])
            return i + 1;
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// պոչային կանչ

const int* rec_lsr(const int* begin, const int* end, int x)
{
    if (begin == end)
        return end;
    return *begin == x ? begin : rec_lsr(begin + 1, end, x);
}

const int* itr_lsr(const int* begin, const int* end, int x)
{
    for (; begin != end; ++begin)
        if (*begin == x)
            break;

    return begin;
}


///////////////////////////////////////////////////////////////////////////////
// երկուական որոնում

const int* rec_bsl(const int* begin, const int* end, int x)
{
    const auto mid = begin + (end - begin) / 2;
    if (mid == begin)
        return begin == end || *begin < x ? end : begin;

    return *mid < x ?
        rec_bsl(mid + 1, end, x)
        : rec_bsl(begin, mid, x);
}


const int* itr_bsl(const int* begin, const int* end, int x)
{
    while (true)
    {
        const auto mid = begin + (end - begin) / 2;
        if (mid == begin)
            return begin == end || *begin < x ? end : begin;

        if (*mid < x)
            begin = mid + 1;
        else
            end = mid;
    }
}


typedef const int* (*bsl_variant)(const int*, const int*, int);
int test_bsl(bsl_variant bsl)
{
    const int data[] = { 0, 0, 0, 1, 1, 1, 1, 2, 3, 5, 10, 11, 11, 11, 20 };
    const struct {
        int b, e, x, r;
    } ts[] =
    {
      { 0, 15, 0, 0 }, //1
      { 0, 15, 1, 3 }, //2
      { 0, 15, 2, 7 }, //3
      { 0, 15, 3, 8 }, //4
      { 0, 15, 5, 9 }, //5
      { 0, 15, 4, 9 }, //6
      { 0, 15, 7, 10 },  //7
      { 0, 15, 10, 10 }, //8
      { 0, 15, 11, 11 }, //9
      { 0, 15, 20, 14 }, //10
      { 0, 15, 25, 15 }, //11
      { 0, 0, 10, 0 }, //12
      { 0, 1, 0, 0 },  //13
      { 0, 1, 10, 1 }, //14
      { 0, 2, 2, 2 },  //15
      { 0, 2, 0, 0 },  //16
      { 0, 3, 2, 3 },  //17
      { 0, 3, 0, 0 },  //18
      { 0, 4, 2, 4 },  //19
      { 0, 4, 1, 3 },  //20
      { 0, 4, 0, 0 },  //21
      { 1, 5, 2, 5 },  //22
      { 1, 5, 1, 3 },  //23
      { 1, 5, 0, 1 },  //24
      { 2, 6, 2, 6 },  //25
      { 2, 6, 1, 3 },  //26
      { 2, 6, 0, 2 },  //27
      { 13, 15, 15, 14 } //28
    };
    int test = 0;
    for (auto& t : ts)
    {
        ++test;
        if (bsl(data + t.b, data + t.e, t.x) - data != t.r)
            return test;
    }

    return 0;
}









#include <iostream>
#include <cstdlib>

void report(int test_result, const char* msg)
{
    if (test_result)
        std::cout << msg << ": " << test_result << std::endl;
}

int main()
{
    using namespace std;

    cout << "Testing factorial variants:\n"; // ֆակտորիալի ստուգում
    {
        const struct {
            fact_variant fact;
            const char* name;
        } vs[] =
        {
          { rec_fact, "rec" },
          { tcr_fact_caller, "tcr" },
          { itr_fact_0, "itr0" },
          { itr_fact, "itr" }
        };
        for (auto& v : vs)
            report(test_fact(v.fact), v.name);
    }

    cout << "done.\nTesting fib variants:\n";// Ֆիբոնաչիի ստուգում
    {
        const struct {
            fib_variant fib;
            const char* name;
        } vs[] =
        {
          { rec_fib, "rec" },
          { tcr_fib_caller, "tcr" },
          { itr_fib_0, "itr0" },
          { itr_fib, "itr" }
        };
        for (auto& v : vs)
            report(test_fib(v.fib), v.name);
    }

    cout << "done.\nTesting binary search variants:\n";// երկուական որոնման ստուգում
    {
        const struct {
            bsl_variant bsl;
            const char* name;
        } vs[] =
        {
          { rec_bsl, "rec" },
          { itr_bsl, "itr" }
        };
        for (auto& v : vs)
            report(test_bsl(v.bsl), v.name);
    }

    cout << "done." << endl;
    return EXIT_SUCCESS;
}
