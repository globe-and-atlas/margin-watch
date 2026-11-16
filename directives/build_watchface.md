---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T15:20:00-06:00"
---
# Build watchface
Generate numeral masks with `python3 execution/generate_digits.py`.
Run `node watchface/settings.test.js` and `python3 -m pytest tests/ -q`.
Run `python3 execution/build.py` then `python3 execution/verify.py`.
Fixture builds use MARGIN_FIXTURE=1 after pebble clean; never copy fixtures to release.
Native QA must use the sole shared Emery emulator serially.
