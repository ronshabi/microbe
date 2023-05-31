#include <kernel/Libk.h>
#include <kernel/Printk.h>
#include <kernel/Types.h>
#include <kernel/VGA.h>

extern VGA* g_VGA;

enum printk_mode
{
    printk_mode_normal,
    printk_mode_get_type,
};

void PrintUnsigned(usize base, usize number, char* buffer)
{
    const char* alphanum = "0123456789abcdef";
    usize buffer_index = 0;

    if (number == 0)
    {
        buffer[0] = '0';
        return;
    }

    while (number > 0)
    {
        usize digit = number % base;
        buffer[buffer_index] = alphanum[digit];
        buffer_index++;
        number /= base;
    }

    strrev(buffer);
}

void vsnprintk(char* buffer, usize n, const char* fmt, va_list v)
{
    // The buffer should come memzero'd already!

    int mode = printk_mode_normal;
    usize buf_index = 0;

    const usize tempbuf_size = 64;
    char tempbuf[tempbuf_size];
    usize tempbuf_index = 0;

    while (*fmt && buf_index < n)
    {
        char c = *fmt++;

        if (mode == printk_mode_normal)
        {

            if (c == '%')
                mode = printk_mode_get_type;
            else
                buffer[buf_index++] = c;
        }
        else if (mode == printk_mode_get_type)
        {
            // Advance fmt_index to the next space
            while (*fmt != ' ' && *fmt != '\0' && *fmt != '\n' && *fmt != '[' && *fmt != ']')
                fmt++;

            memset(tempbuf, 0, tempbuf_size);

            switch (c)
            {
            case 'x':
                PrintUnsigned(16, va_arg(v, u32), tempbuf);
                goto copy_number_from_buffer;

            case 'd':
                PrintUnsigned(10, va_arg(v, u32), tempbuf);
                goto copy_number_from_buffer;

            copy_number_from_buffer:
                tempbuf_index = 0;
                while (*(tempbuf + tempbuf_index) && buf_index < n)
                {
                    buffer[buf_index++] = *(tempbuf + tempbuf_index);
                    tempbuf_index++;
                }
                mode = printk_mode_normal;
                break;

            case 's': {
                const char* str_argument = va_arg(v, const char*);

                if (str_argument == NULL)
                {
                    str_argument = "(null)";
                }

                const usize str_argument_length = strlen(str_argument);
                usize str_argument_i = 0;

                while (buf_index < n && str_argument_i < str_argument_length)
                {

                    buffer[buf_index++] = str_argument[str_argument_i];
                    str_argument_i++;
                }

                mode = printk_mode_normal;
                break;
            }
            default:
                // Pop the variadic argument anyway
                va_arg(v, u32);
                buffer[buf_index++] = '?';
                mode = printk_mode_normal;
                break;
            }
        }

        /* Normal character */
    }
}

void printk(const char* fmt, ...)
{
    va_list v;
    va_start(v, fmt);
    const usize buffer_size = 512;
    char buffer[buffer_size];
    memset(buffer, 0, buffer_size);
    vsnprintk(buffer, buffer_size, fmt, v);
    g_VGA->PutString(buffer);
    va_end(v);
}

void errprintk(const char* fmt, ...)
{
    va_list v;
    va_start(v, fmt);
    const usize buffer_size = 512;
    char buffer[buffer_size];
    memset(buffer, 0, buffer_size);
    vsnprintk(buffer, buffer_size, fmt, v);
    g_VGA->SetColor(VGA::White, VGA::Red);
    g_VGA->PutString(buffer);
    g_VGA->SetColor(VGA::White, VGA::Black);
    va_end(v);
}