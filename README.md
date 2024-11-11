## ASADAS Inventory and Order Management System

This program is designed for Associations that Manage Water and Sewer Systems (ASADAS) to efficiently manage the entry of spare parts into inventory and orders for parts needed for repairs by staff. 

### Menu Options
1. **Inventory**
    - Enter part into inventory
    - Consult part in inventory
    - Modify part in inventory
    - Delete part from inventory
2. **Order**
    - Enter order
    - Order consultation
    - Cancel order
    - Register order delivery
3. **Inventory Report**
4. **Order Report**
6. **Exit**

### Inventory Management
- Record parts in inventory with:
    1. Part code (e.g., P00000890)
    2. Name of the part
    3. Cost of the part per unit
    4. Quantity of parts
    5. Name of the company providing the parts
    6. Invoice of the company providing the parts
    7. ID number of the person entering the parts
- Information stored in INVENTORY.TXT file

### Order Management
- Record orders with:
    1. Order code (e.g., PE00000890)
    2. Part code
    3. Quantity of parts requested
    4. Employee identification number
    5. Request date (DD/MM/YYYY)
    6. Order status: Canceled, Delivered, or In process
- Information stored in ORDERS.TXT file

### Reports
- **Inventory Report** shows:
    - Code
    - Piece Name
    - Cost
    - Quantity
    - Company Name
    - Invoice #
    - ID of the person entering the part
- **Order Report** shows:
    - Code
    - Order Code
    - Piece
    - Quantity
    - ID of the person requesting
    - Date Request
    - Status

### Return to Main Menu
After generating a report, the program will ask if you want to return to the main menu. Enter "S" for Yes, or "N" for No.
