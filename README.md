# Relic-bbs-fault-injection
Contains a pdf (CVE_report_relic.pdf) vulnerability report for BB short signature in relic library. Here are some abstract of our code in src directory.
## memory-profiling
Code in this directory can be used for attacker's offline memory profiling, which is a preparation for online fault injection attack.
## attack-bbsign
Code in this directory can be used for attacker's online fault injection attack.
## offline.c
Offline.c is attacker's code. This code process the faulty signature and leak the original bit of the signer's secret key.

For more explanation such as theoretical analysis and experiment evaluation, we highly recommend you to read CVE_report_relic.pdf.
