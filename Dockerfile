# ===========================================================================
# DOCKERFILE: cxx.simplelog (multistage build)
# ===========================================================================
# SEE ALSO:
#   https://docs.docker.com/develop/develop-images/multistage-build/
# ===========================================================================

# ---------------------------------------------------------------------------
# STAGE: buildenv
# ---------------------------------------------------------------------------
FROM cxx_alpine:latest AS buildenv
WORKDIR /workdir/cxx.simplelog
COPY . .
# RUN CMAKE_BUILD_CONFIG=host_debug cmake-build cleanup build test
RUN CMAKE_BUILD_CONFIG=release cmake-build build install --prefix=staging


# ---------------------------------------------------------------------------
# STAGE: product -- Installed libs, headers (only end products)
# ---------------------------------------------------------------------------
# NOTE: product image contains only build results from image:buildenv
FROM alpine:latest AS product
RUN apk --no-cache add ca-certificates
WORKDIR /opt/cxx.simplelog
COPY --from=buildenv /workdir/cxx.simplelog/build.release/staging/ .
CMD ["/bin/sh"]
