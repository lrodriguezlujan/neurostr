---
currentSection: class
currentSubsection: log
currentItem:
---

# namespace `log` {#namespace_log}

Log namespace contains logger functions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``_logger_storage``](#class_log___logger__storage)        |
`public `[`_logger_storage`](#class_log___logger__storage)` _nstr_logger_` |
`public void init_log_file(const std::string & path)` | Inits file logger.
`public void init_log_cout()` | Initializes the logger using the standard output stream.
`public void init_log_cerr()` | Initializes the logger using the standard error stream.
`public void disable_log()` | Disables the log.
`public void enable_log()` | Enables the log.
`public void set_format(const std::string & s)` | Changes current log format.
`public void set_level(`[`severity_level`](#class_log_1a10acfc5ebf7a1e159905211f5b89d5df)` l)` | Changes current logger severity threshold.

## Members

### `class `[``_logger_storage``](#class_log___logger__storage) {#class_log___logger__storage}




---

### `public `[`_logger_storage`](#class_log___logger__storage)` _nstr_logger_` {#class_log_1a984a1855bc6a5c245694cc82ff57971d}



---

### `public void init_log_file(const std::string & path)` {#class_log_1a48d077acbac6ac01f3605148c730d875}

Inits file logger.

#### Parameters
* `path` Log file path


* `format_string` Log format string

---

### `public void init_log_cout()` {#class_log_1ab2b3050ad2290fab7f70240fe5301d16}

Initializes the logger using the standard output stream.



---

### `public void init_log_cerr()` {#class_log_1a90aae804b2165f9096a0f3e9169064e8}

Initializes the logger using the standard error stream.



---

### `public void disable_log()` {#class_log_1ac9f76b76648284199b443ad854880870}

Disables the log.



---

### `public void enable_log()` {#class_log_1ae9ad352b1550bcb04cd61c79851a1850}

Enables the log.



---

### `public void set_format(const std::string & s)` {#class_log_1a0b6257a88c688767caa28ce5bb40bc65}

Changes current log format.



---

### `public void set_level(`[`severity_level`](#class_log_1a10acfc5ebf7a1e159905211f5b89d5df)` l)` {#class_log_1a829dfdf9fe0c8f2ecdf61a1726c553e1}

Changes current logger severity threshold.

---

# class `_logger_storage` {#class_log___logger__storage}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline void set(std::shared_ptr< spdlog::logger > && l)` | Changes the current logger (From spdlog=.
`public inline void set_level(`[`severity_level`](#class_log_1a10acfc5ebf7a1e159905211f5b89d5df)` l)` | Changes the severity level threshold.
`public inline void set_format(const std::string & fmt)` | Changes output format string.
`public inline void enable()` | Activates logger functions.
`public inline void disable()` | Deactivates logger functions.
`public inline bool status() const` | Returns the current logger status.
`public inline spdlog::logger & get()` |

## Members

### `public inline void set(std::shared_ptr< spdlog::logger > && l)` {#class_log___logger__storage_1a6612b71c668892b02cd5d637902c45ab}

Changes the current logger (From spdlog=.

#### Parameters
* `l` New logger

---

### `public inline void set_level(`[`severity_level`](#class_log_1a10acfc5ebf7a1e159905211f5b89d5df)` l)` {#class_log___logger__storage_1afef168c7dc7970789a129a238ff88ec2}

Changes the severity level threshold.

#### Parameters
* `l` New severity level

---

### `public inline void set_format(const std::string & fmt)` {#class_log___logger__storage_1a7df8ac82aa171e3256f183d56c24bc88}

Changes output format string.

#### Parameters
* `fmt` Format string

---

### `public inline void enable()` {#class_log___logger__storage_1ac741ea4149344295079d2c1031809da3}

Activates logger functions.



---

### `public inline void disable()` {#class_log___logger__storage_1a492a41e65d87495d7de4923776ca58cd}

Deactivates logger functions.



---

### `public inline bool status() const` {#class_log___logger__storage_1a08620b7615d29c463df3c5bb342a0b89}

Returns the current logger status.

#### Returns
True if the logger is active

### `public inline spdlog::logger & get()` {#class_log___logger__storage_1a383bc0606df6fa0561332a6721768077}
