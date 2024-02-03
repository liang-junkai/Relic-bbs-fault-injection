# Leak the Secret Key of BBS Short Signature in Relic via Rowhammer
More details can be found in this repo related to **CVE-2023-51939**, we decribe our theoretical analysis and experiment results below.

## Overview
We cloned the relic repo from github on December 10, 2023 and have analyzed the source code of the Boneh Boyen short signature (or bbs) scheme (more precisely, [relic_cp_bbs.c](https://github.com/relic-toolkit/relic/blob/main/src/cp/relic_cp_bbs.c)). Based on our analysis, the signature implementation (Line 70 in relic_cp_bbs.c) is vulnerable to fault attacks.

As a proof-of-concept (PoC), we have recovered 190 bits out of 224 secret bits via Rowhammer. In technology aspect, Rowhammer is software-induced DRAM fault, which can induce bit flips in main memory that runs a commodity system. In our PoC, a malicious user process co-resides in the same system with a victim process that runs the bbs short signature from the relic library. As both processes share the main memory, the adversary can induce bit flips to the secret key before it is used by the victim to sign a message, resulting in a faulty signature. With enough faulty signatures released, the adversary can recover/leak the secret key. For more details of the analysis, PoC and possible countermeasures, they are provided in the following page.

Before our report, RSA implementation in the WolfSSL library and the OpenSSL library have been reported to be vulnerable to Rowhammer-based fault attacks. For the WolfSSL library, its vulnerability is tracked via [CVE-2019-19962](https://nvd.nist.gov/vuln/detail/CVE-2019-19962). For the OpenSSL library, its RSA vulnerability is tracked by a [commit]( https://github.com/openssl/openssl/pull/7225/commits/02534c1ee3e84a1d6c59a887a67bd5ee81bcf6cf).  Clearly, we target a different cryptographic algorithm, i.e., bbs signature. 

## Theoretical Analysis
We presented theoretical analysis of how this fault injection attack towards bbs signature works in attachment theoretical.pdf. For more details, read the pdf.

## Experiment Evaluation
The experiment result and code of this fault injection attack via Rowhammer can be found in attachment experiment.pdf. For more details, read the pdf.

## Support
Feel free to submit Github issues, pull requests, or contact the following maintainers.

- Junkai Liang: [Github](https://github.com/liang-junkai), [Email](ljknjupku@gmail.com)
- Zhi Zhang: [Github](https://github.com/zhangzhics), [Email](zzhangphd@gmail.com)
- Xin Zhang: [Github](https://github.com/zhangxin00), [Email](zhangxin00@stu.pku.edu.cn)
- Qingni Shen: [Github](https://github.com/PKU-RoC), [Email](qingnishen@pku.edu.cn)
