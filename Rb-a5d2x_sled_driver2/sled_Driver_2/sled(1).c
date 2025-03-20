#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

struct gpio_desc *Led;

struct my_struct {
    struct platform_device *pdev;
    struct miscdevice mdev;
};

static inline struct my_struct *to_my_struct(struct file *file)
{
    struct miscdevice *miscdev = file->private_data;

    return container_of(miscdev, struct my_struct, mdev);
}

static long Sled_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
int value;
         switch(cmd) {
                case WR_VALUE:
                        if( copy_from_user(&value ,(int32_t*) arg, sizeof(value)) )
                        {
                                pr_err("Data Write : Err!\n");
                        }
                        printk("Value = %d\n", value);
			gpiod_set_value(Led,value);
	
                        break;
                case RD_VALUE:
                        if( copy_to_user((int32_t*) arg, &value, sizeof(value)) )
                        {
                                printk("Data Read : Err!\n");
                        }
                        break;
                default:
                        printk("Default\n");
                        break;
        }
        return(0);
}

static const struct file_operations my_fops = {
    .owner  = THIS_MODULE,
    .unlocked_ioctl   = Sled_ioctl,
};

static int gpio_init_probe(struct platform_device *pdev)
{
	struct my_struct *my;
    int ret;

    printk("SLED Probe Called\n");
   
 
    my = kmalloc(sizeof(*my), GFP_KERNEL);
    if (!my) {
        return -ENOMEM;
	}

    platform_set_drvdata(pdev, my);
    my->pdev = pdev;

    my->mdev.minor  = MISC_DYNAMIC_MINOR;
    my->mdev.name   = "my_led";
    my->mdev.fops   = &my_fops;
    my->mdev.parent = NULL;

    ret = misc_register(&my->mdev);
    if (ret) {
        dev_err(&pdev->dev, "Failed to register miscdev\n");
        return ret;
    }

    dev_info(&pdev->dev, "Registered\n");

    Led = devm_gpiod_get(&pdev->dev, "led", GPIOD_OUT_LOW);
	
     return(0);
}

static int gpio_exit_remove(struct platform_device *pdev)
{
   struct my_struct *my = platform_get_drvdata(pdev);
   
   printk("GPIO example exit\n");
   
   misc_deregister(&my->mdev);
   kfree(my);
   dev_info(&pdev->dev, "Unregistered\n");

   return(0);
}

static struct of_device_id gpio_match[] = {
    {.compatible = "sled"}
};

static struct platform_driver gpio_driver = {
    .probe  = gpio_init_probe,
    .remove = gpio_exit_remove,
    .driver = {
		.name = "sled",
                .owner = THIS_MODULE,
                .of_match_table = gpio_match,
    }
};
 
module_platform_driver(gpio_driver);

MODULE_AUTHOR("Gopal");
MODULE_DESCRIPTION("Gpio example");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio_driver");
