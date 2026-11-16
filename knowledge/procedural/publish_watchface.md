---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-05T21:35:28-06:00"
---
# Publish a GIF-first native release
- `python3 execution/build_store_media.py` creates exact native palette GIF frames, explicit holds, four static previews, icons and manifest.
- `python3 execution/publish.py` validates a dry-run plan. `--publish` performs the authorized upload through the signed-in SDK.
- SDK auth owns tokens; scripts never read or print them. No fixture environment variables survive the clean production build.
- Publish uses `--non-interactive --is-published --no-gif-all-platforms --replace-screenshots` with the GIF first.
- New apps receive description and icons from explicit files. SDK existing-app updates do not update creation-only copy/icon fields.
- Archive the exact PBW from the publish command, because SDK timestamp metadata can differ between rebuilds.
- `python3 execution/verify_public.py` reads the public HTML, confirms version and gallery order, downloads assets, compares GIF/PBW bytes and PNG pixels.
- The public PBW endpoint redirects to the store's R2 storage host. Follow that verified host without logging signed query parameters.
- Public verification HTTP requests have30s timeouts, bounded transient retries, no auth-error retries and gallery de-duplication tests.
- A receipt prevents blind duplicate publication; inspect the existing release before intentionally publishing another version.
