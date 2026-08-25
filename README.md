# Cloud PC Status Logger

A lightweight C-based Linux monitoring tool that collects PC resource information and periodically uploads it to a Supabase cloud database.

## Features

* CPU load monitoring
* RAM usage monitoring
* Disk usage monitoring
* PC hostname detection
* Health score calculation
* Healthy / Warning / Critical status
* Cloud heartbeat monitoring
* Supabase REST API integration
* Continuous monitoring every 10 seconds
* One-time monitoring mode

## Tech Stack

* **C**
* **Linux**
* **libcurl**
* **Supabase**
* **PostgreSQL**
* **REST API**
* **Makefile**

## Project Structure

```text
cloud-pc-status/
├── main.c
├── system_info.c
├── system_info.h
├── cloud.c
├── cloud.h
├── health.c
├── health.h
├── schema.sql
├── Makefile
└── .gitignore
```

## How It Works

```text
Linux PC
   ↓
CPU / RAM / Disk
   ↓
Health Calculation
   ↓
C Monitoring Program
   ↓
libcurl REST API
   ↓
Supabase
   ↓
pc_status table
```

The program collects system information, calculates a simple health score, and uploads the latest status to Supabase.

## Setup

Set your Supabase credentials as environment variables:

```bash
export SUPABASE_URL="your_supabase_url"
export SUPABASE_KEY="your_supabase_publishable_key"
```

Compile the project:

```bash
make
```

## Run

For continuous monitoring:

```bash
./cloud_status
```

The program uploads the PC status every 10 seconds.

For a single check:

```bash
./cloud_status once
```

## Database

Create the required `pc_status` table and columns using the SQL provided in:

```text
schema.sql
```

The table stores information such as:

* Hostname
* CPU usage
* RAM usage
* Disk usage
* Health score
* Health status
* Heartbeat
* Timestamp

## Example

```text
============================
      CLOUD PC STATUS
============================

Hostname : DESKTOP-QH9P3E7
CPU Load : 0.04
RAM      : 17.9%
Disk     : 1.0%

Health   : 100/100
Status   : HEALTHY
Heartbeat: ONLINE

Uploading to cloud...
Status uploaded to cloud successfully.
Next update in 10 seconds...
```

## Security

Supabase credentials are provided through environment variables and are **not stored in the source code**.

The executable and environment files are excluded using `.gitignore`.

## Purpose

This project demonstrates Linux system monitoring, modular C programming, REST API communication, cloud database integration, and basic cloud-based PC health monitoring.
