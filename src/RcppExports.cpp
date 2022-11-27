// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// murmurhash
void murmurhash(std::string key, uint64_t seed);
RcppExport SEXP _bloomR_murmurhash(SEXP keySEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    Rcpp::traits::input_parameter< uint64_t >::type seed(seedSEXP);
    murmurhash(key, seed);
    return R_NilValue;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_BloomFilter();

static const R_CallMethodDef CallEntries[] = {
    {"_bloomR_murmurhash", (DL_FUNC) &_bloomR_murmurhash, 2},
    {"_rcpp_module_boot_BloomFilter", (DL_FUNC) &_rcpp_module_boot_BloomFilter, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_bloomR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
