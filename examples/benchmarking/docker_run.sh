#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE_NAME="${IMAGE_NAME:-benchmarking-dev:ubuntu24-clang20}"
CONTAINER_NAME="${CONTAINER_NAME:-benchmarking-dev}"

docker run --rm -it \
  --name "${CONTAINER_NAME}" \
  --privileged \
  --pid=host \
  --cap-add SYS_ADMIN \
  --cap-add SYS_PTRACE \
  --security-opt seccomp=unconfined \
  -v "${REPO_ROOT}:/workspace" \
  -w /workspace/examples/benchmarking \
  "${IMAGE_NAME}" \
  bash
