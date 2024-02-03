# Leak the Secret Key of BBS Short Signature in Relic via Rowhammer
More details can be found in this repo related to [**CVE-2023-51939**](https://nvd.nist.gov/vuln/detail/CVE-2023-51939), we decribe our theoretical analysis and experiment results below.

## Background
We cloned the relic repo from github on December 10, 2023 and have analyzed the source code of the Boneh Boyen short signature (or bbs) scheme (more precisely, [relic_cp_bbs.c](https://github.com/relic-toolkit/relic/blob/main/src/cp/relic_cp_bbs.c)). Based on our analysis, the signature implementation (Line 70 in relic_cp_bbs.c) is vulnerable to fault attacks.

As a proof-of-concept (PoC), we have recovered 190 bits out of 224 secret bits via Rowhammer. In technology aspect, Rowhammer is software-induced DRAM fault, which can induce bit flips in main memory that runs a commodity system. In our PoC, a malicious user process co-resides in the same system with a victim process that runs the bbs short signature from the relic library. As both processes share the main memory, the adversary can induce bit flips to the secret key before it is used by the victim to sign a message, resulting in a faulty signature. With enough faulty signatures released, the adversary can recover/leak the secret key. For more details of the analysis, PoC and possible countermeasures, they are provided in the following page.

Before our report, RSA implementation in the WolfSSL library and the OpenSSL library have been reported to be vulnerable to Rowhammer-based fault attacks. For the WolfSSL library, its vulnerability is tracked via [CVE-2019-19962](https://nvd.nist.gov/vuln/detail/CVE-2019-19962). For the OpenSSL library, its RSA vulnerability is tracked by a [commit]( https://github.com/openssl/openssl/pull/7225/commits/02534c1ee3e84a1d6c59a887a67bd5ee81bcf6cf).  Clearly, we target a different cryptographic algorithm, i.e., bbs signature. 

## Theoretical Analysis
We presented theoretical analysis of how this fault injection attack towards bbs signature works in attachment theoretical.pdf. For more details, please read the pdf.

## Experiment Evaluation
The experiment result and code of this fault injection attack via Rowhammer can be found in attachment experiment.pdf. For more details, please read the pdf.

## Mitigating the Fault-Injection Attack
An effective mitigation is to *verify the signature after signing a message*. This countermeasure has been used by the OpenSSL and the WolfSSL library to mitigate the Rowhammer attack against the RSA implementation \[1,2\]. To this end, when updating the bbs scheme implementation, verification is added right after the signature generation. More precisely, we can use the aforementioned *cp_bbs_ver* function. If the verification fails, the *cp_bbs_sign* will not generate a signature. By doing so, {the fault can be detected and no faulty signature can be leveraged by the adversary.} Compared to signing, verification is much faster, thus making the performance overhead acceptable.

\[1\] Openssl commit: Add a protection against fault attack on message v2. 2018. URL: https://github.com/openssl/openssl/pull/7225/commits/02534c1ee3e84a1d6c59a887a67bd5ee81bcf6cf.

\[2\] WolfSSL Release 5.5.0 (Aug 30, 2022). 2022. URL: https://github.com/wolfSSL/wolfssl/releases/tag/v5.5.0-stable.
## Support
Feel free to submit Github issues, pull requests, or contact the following maintainers.

- Junkai Liang: [Github](https://github.com/liang-junkai), [Email](ljknjupku@gmail.com)
- Zhi Zhang: [Github](https://github.com/zhangzhics), [Email](zzhangphd@gmail.com)
- Xin Zhang: [Github](https://github.com/zhangxin00), [Email](zhangxin00@stu.pku.edu.cn)
- Qingni Shen: [Github](https://github.com/PKU-RoC), [Email](qingnishen@pku.edu.cn)
