#!/bin/bash

current_date=$(date +%Y-%m-%d)

folder_path="./day_by_day"
file_name="${current_date}.md"
file_path="${folder_path}/${file_name}"

touch "${file_path}"
# chmod 666 "${file_path}"
nvim "${file_path}"
