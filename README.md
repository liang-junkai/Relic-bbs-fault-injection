# Leak the Secret Key of BBS Short Signature in Relic via Rowhammer
More details can be found in this repo related to **CVE-2023-51939**, we decribe our theoretical analysis and experiment results below.

We cloned the relic repo from github on December 10, 2023 and have analyzed the source code of the Boneh Boyen short signature (or bbs) scheme (more precisely, [relic_cp_bbs.c](https://github.com/relic-toolkit/relic/blob/main/src/cp/relic_cp_bbs.c)). Based on our analysis, the signature implementation (Line 70 in relic_cp_bbs.c) is vulnerable to fault attacks.
