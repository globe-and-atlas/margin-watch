---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T21:30:16-06:00"
---
# Publish watchface
Authorization: Daniel approved publishing this0.1.0 release with a palette GIF as first preview.
1. Generate media using `python3 execution/build_store_media.py`.
2. Run host/settings tests and production bundle verification.
3. Fresh reviewer checks GIF timing, source identity, preview order and copy.
4. Publish through the signed-in Pebble SDK CLI with explicit screenshots in filename order, `--is-published`, `--no-gif-all-platforms`, and creation description/icons.
5. Archive the exact SDK-produced published PBW after publishing; clean rebuild timestamps can change bytes.
6. Fetch the public listing until new assets appear. Verify GIF first, exact GIF/PBW bytes, four PNG RGB matches.
7. Record app ID, URL, version and SHA256 in release metadata and SESSION.md.
Never print authentication tokens. Do not retry ambiguous creation blindly: inspect CLI result/public identity first.
