# Relic-bbs-fault-injection
Contains a pdf vulnerability report for BB short signature in relic library. (CVE_report_relic.pdf)
## memory-profiling
Code in this directory can be used for attacker's offline memory profiling, which is a preparation for online fault injection attack.
## attack-bbsign
Code in this directory can be used for attacker's online fault injection attack.
## offline.c
Offline.c is attacker's code. This code process the faulty signature and leak the original bit of the signer's secret key.
