#!/bin/bash
search /var/lib/apt/lists/* -l "Package: ${1}.*"
