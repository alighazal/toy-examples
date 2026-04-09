#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_NAME="${IMAGE_NAME:-benchmarking-dev:ubuntu24-clang20}"

docker build \
  -f "${SCRIPT_DIR}/Dockerfile" \
  -t "${IMAGE_NAME}" \
  "${SCRIPT_DIR}"

echo "Built image: ${IMAGE_NAME}"
