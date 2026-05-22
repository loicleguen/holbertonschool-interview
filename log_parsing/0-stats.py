#!/usr/bin/python3
"""Log parsing script."""

import re
import sys


STATUS_CODES = (200, 301, 400, 401, 403, 404, 405, 500)
LOG_PATTERN = re.compile(
    r"^(\d{1,3}(?:\.\d{1,3}){3}) - "
    r"\[(.*?)\] "
    r'"GET /projects/260 HTTP/1\.1" '
    r"(\d{3}) "
    r"(\d+)$"
)


def print_stats(total_size, status_count):
    """Print the accumulated statistics."""
    print("File size: {}".format(total_size))
    for code in STATUS_CODES:
        count = status_count.get(code)
        if count:
            print("{}: {}".format(code, count))


def main():
    """Read stdin and print stats every 10 lines and on interrupt."""
    total_size = 0
    line_count = 0
    status_count = {}

    try:
        for line in sys.stdin:
            line_count += 1
            match = LOG_PATTERN.match(line.strip())
            if not match:
                if line_count % 10 == 0:
                    print_stats(total_size, status_count)
                continue

            status = int(match.group(3))
            file_size = int(match.group(4))

            total_size += file_size
            if status in STATUS_CODES:
                status_count[status] = status_count.get(status, 0) + 1

            if line_count % 10 == 0:
                print_stats(total_size, status_count)

    except KeyboardInterrupt:
        print_stats(total_size, status_count)
        raise


if __name__ == "__main__":
    main()
