---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T15:40:00-06:00"
---
# Errors —2026-11-05
## Stale emulator foreground
SDK install reported success while LCD Club stayed visible. Confirmed with native screenshot, backed up emulator flash to .tmp, gracefully stopped owned emulator, wiped emulator-only data, then reinstalled. Pixel assertions then passed. Never accept install text as renderer evidence.
## Working-directory edit mismatch
A root-relative edit was run from watchface and failed before a later independent build. Fixed by absolute Path; use separate commands for source mutations and SDK builds.

##2026-11-05 — Public PBW storage redirect
Initial public verifier rejected the PBW endpoint redirect because its host allowlist contained only RePebble domains. Observed the public endpoint redirect hostname, allowed the exact store R2host, and verified downloadedPBW SHA256. No signed URL query is logged.

## 2026-11-06 — Preserve minute-strip meaning
Error: an early round adaptation made the lower accent strip duplicate battery charge.
Fix: keep the battery percentage label, but restore the strip to minute progress. Native midnight/late captures verify empty/full endpoints.
Graduated-to: round_digital.h.
