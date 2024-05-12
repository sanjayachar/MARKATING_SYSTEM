# Market System 

## Project Overview
This Market System is a console-based C++ application designed to facilitate the management of a Market System's inventory and handle transactions. The system enables administrators to manage product listings effectively and allows buyers to make purchases and view detailed receipts.

## Key Features
- **Administrator Authentication**: Secure login for administrators to access management features.
- **Product Management**: Comprehensive tools for administrators to add, edit, delete, and list products.
- **Shopping Cart**: Allows buyers to select products, specify quantities, and purchase them.
- **Receipt Generation**: Automatically generates a receipt after purchase, detailing the items bought and the total amount, including discounts if applicable.

## Function Descriptions
### Administrator Functions
- **`add()`**: This function prompts the administrator to enter product details such as product code, name, price, and discount. It checks for the uniqueness of product codes to prevent duplication in the database.
- **`edit()`**: Enables the administrator to modify existing product information. It requires the product code to fetch the current details and allows editing of any product attribute including name, price, or discount.
- **`rem()`**: Allows for the removal of a product from the inventory. The administrator must provide the product code of the item to be deleted, ensuring that only existing products are targeted for deletion.
- **`list()`**: Displays all the products currently available in the Market System's inventory, including their codes, names, prices, and applicable discounts.

### Buyer Functions
- **`receipt()`**: Manages the buying process. Buyers can choose products by entering their codes, specify the quantity they wish to purchase, and then finalize their order. A receipt is generated which lists all products bought, their prices, total amount, and total amount after applying discounts.

## Installation
To install and run this system on your machine, follow these steps:
1. Clone this repository to your local machine using:
   ```bash
   git clone https://github.com/sanjayachar/MARKATING_SYSTEM.git

2.  Compile the program using a C++ compiler that supports C++11 or later. For example, you can use g++:

    `g++ -o MarketSystem main.cpp -std=c++11`
    
4.  Run the compiled application:
   `./MarketSystem`

### Usage
    Starting the Application: Launch the application executable. The main menu will offer options to log in as an administrator or continue as a buyer.
    Administrator Login: Administrators need to authenticate by entering their credentials to access the product management functionalities.
    Buyer Access: Buyers can directly access the shopping menu to start purchasing products without logging in.
    Exiting the Program: Users can exit the application at any point by selecting the exit option from the main menu.

