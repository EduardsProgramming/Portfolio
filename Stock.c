#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define p printf
#define s scanf
#define PRODUCT_COUNT 10000
#define SALES_COUNT 10000
#define CHARACTER_LIMIT 20

typedef struct
{
    int productCode;
    char productName[CHARACTER_LIMIT];
    int stock;
    int soldQuantity;
} Product;

typedef struct
{
	int day;
	int month;
	int year;
} Date;

typedef struct
{
    int productCode;
    int productName[CHARACTER_LIMIT];
    Date selldate;
    int quantity;
} Sale;

int menu();
void initializeVector(Product[]);
void addProduct(Product[], int*, int*, int*);
void displayVector(Product[], int*);
void sortByProductCode(Product[], Product[], int*);
void sortByProductName(Product[], Product[], int*);
void sortByProductStock(Product[], Product[], int*);
void modifyStock(Product[]);
void modifyProductData(Product[]);
void deleteProduct(Product[], int*);
void addSale(Sale[], Product[], int);


int main()
{
    int option, productCounter, lastCode, salesCounter, deletedCode;
    productCounter = 0;
    lastCode = 0;
    salesCounter = 0;
	deletedCode = 0;
    Product productVector[PRODUCT_COUNT];
    Sale saleVector[SALES_COUNT];
    initializeVector(productVector);

    do
    {
        option = menu();
		Product codeSortedProductVector[PRODUCT_COUNT];
        Product nameSortedProductVector[PRODUCT_COUNT];
        Product stockSortedProductVector[PRODUCT_COUNT];

		switch (option)
        {
        case 1:
            if (productCounter < PRODUCT_COUNT)
            {
                addProduct(productVector, &productCounter, &lastCode, &deletedCode);
            }
            else
            {
                printf("Cannot add more products\n");
            }
            break;

        case 2:
            sortByProductCode(productVector, codeSortedProductVector, &productCounter);
            printf("List of products sorted by product code:\n");
            displayVector(codeSortedProductVector, &productCounter);
            system("pause");
            break;

        case 3:
            sortByProductName(productVector, nameSortedProductVector, &productCounter);
            displayVector(nameSortedProductVector, &productCounter);
            system("pause");
            break;
		case 4:
            sortByProductStock(productVector, stockSortedProductVector,&productCounter);
            displayVector(stockSortedProductVector, &productCounter);
            system("pause");
            break;

        case 5:
            modifyStock(productVector);
            break;

		case 6:
			modifyProductData(productVector);
			break;

		case 7:
			deleteProduct(productVector, &productCounter);
			break;

        case 8:
            system("cls");
            addSale(saleVector, productVector, salesCounter);
            break;

        case 9:
            printf("Under construction\n");
            system("pause");
            menu();
            break;

        case 10:
            printf("Until next time\n");
            system("pause");
            break;

        default:
            p("Incorrect option entered\n");
            system("pause");
            break;
        }

    } while (option != 10 && productCounter < PRODUCT_COUNT);

    return 0;
}

/*---------Function Definitions------------*/
int menu()
{
    int op;
    char buffer[100];  // Buffer is added for managing invalid characters

    do {
        system("cls");
        printf("\n\t\t\t           OPTIONS MENU");
        printf("\n\n\t\t\t - Add Product                       <1>");
        printf("\n\n\t\t\t - Sort products by code             <2>");
        printf("\n\n\t\t\t - Sort products by name             <3>");
        printf("\n\n\t\t\t - Sort products by stock            <4>");
        printf("\n\n\t\t\t - Modify stock of a product         <5>");
        printf("\n\n\t\t\t - Modify product data               <6>");
        printf("\n\n\t\t\t - Delete product                    <7>");
        printf("\n\n\t\t\t - Add Sale                          <8>");
        printf("\n\n\t\t\t - Show Sales                        <9>");
        printf("\n\n\t\t\t - Exit                              <10>");
        printf("\n\n\t\t\t - Enter option [1-9] :               ");

        if (scanf("%d", &op) != 1) {
            // for dealing with not numeric numbers
            printf("Invalid input. Please enter a number.\n");
            system("pause");
            scanf("%s", buffer);  // Cleans the entry buffer
            continue;  // returns to the beggining of teh iteration
        }

        if (op < 1 || op > 10) {
            printf("Incorrect option entered\n");
        }

    } while (op < 1 || op > 10);
    return op;
}

void initializeVector(Product productVector[])
{
    for (int i = 0; i < PRODUCT_COUNT; i++)
    {
        productVector[i].productCode = 0;
        strcpy(productVector[i].productName, "");
        productVector[i].stock = 0;
        productVector[i].soldQuantity = 0;
    }
}

void addProduct(Product productVector[], int *productCounter, int *lastCode, int *deletedcode)
{
    system("cls");
    productVector[*productCounter].productCode = (*lastCode) + 1;
    printf("Enter the name of the product with code %d:\n", productVector[*productCounter].productCode);
    getchar();
    gets(productVector[*productCounter].productName);
    printf("Enter the stock quantity of the product %s:\n", productVector[*productCounter].productName);
    scanf("%d", &productVector[*productCounter].stock);
    (*productCounter)++;
    (*lastCode)++;
}


void displayVector(Product productVector[], int *productCounter)
{
    system("cls");
    for (int i = 0; i < *productCounter; i++)
    {
        printf("\nCode: %d\n", productVector[i].productCode);
        printf("Product Name: %s\n", productVector[i].productName);
        printf("Stock: %d\n", productVector[i].stock);
        printf("Quantity sold: %d\n", productVector[i].soldQuantity);
    }
}

void sortByProductCode(Product productVector[], Product codeSortedProductVector[], int *productCounter)
{

    int i, limit, k;
	limit = *productCounter - 1, k = 1;
    for (i = 0; i < *productCounter; i++)
    {
        codeSortedProductVector[i] = productVector[i];
    }

    Product temp;
    while (k)
    {
        k = 0;
        for (i = 0; i < limit; i++)
        {
            if (codeSortedProductVector[i].productCode > codeSortedProductVector[i + 1].productCode)
            {
                temp = codeSortedProductVector[i];
                codeSortedProductVector[i] = codeSortedProductVector[i + 1];
                codeSortedProductVector[i + 1] = temp;
                k = i;
            }
        }
        limit = k;
    }
}

void sortByProductName(Product productVector[], Product nameSortedProductVector[], int *productCounter)
{
    int i, limit = *productCounter - 1, k = 1;
    for (i = 0; i < *productCounter; i++)
    {
       nameSortedProductVector[i] = productVector[i];
    }
    Product temp;

    while (k)
    {
        k = 0;
        for (i = 0; i < limit; i++)
        {
            if (strcmp(nameSortedProductVector[i].productName,nameSortedProductVector[i + 1].productName) > 0)
            {
                temp =nameSortedProductVector[i];
               nameSortedProductVector[i] =nameSortedProductVector[i + 1];
               nameSortedProductVector[i + 1] = temp;
                k = i;
            }
        }
        limit = k;
    }
}
void sortByProductStock(Product productVector[], Product stockSortedProductVector[], int *productCounter)
{

    int i, limit, k;
	limit = *productCounter - 1, k = 1;
    for (i = 0; i < *productCounter; i++)
    {
        stockSortedProductVector[i] = productVector[i];
    }

    Product temp;
    while (k)
    {
        k = 0;
        for (i = 0; i < limit; i++)
        {
            if (stockSortedProductVector[i].stock > stockSortedProductVector[i + 1].stock)
            {
                temp = stockSortedProductVector[i];
                stockSortedProductVector[i] = stockSortedProductVector[i + 1];
                stockSortedProductVector[i + 1] = temp;
                k = i;
            }
        }
        limit = k;
    }
}

void modifyStock(Product productVector[])
{
    system("cls");
    int i, input, codeToSearch, position;
    position = 0;
    input = 0;
    i = 0;
    p("Enter the code of the product whose stock you want to modify\n");
    s("%d", &codeToSearch);

    while (input == 0 && i < PRODUCT_COUNT)
    {
        if (productVector[i].productCode == codeToSearch)
        {
            position = i;
            input = 1;
        }
        i++;
    }

    if (input == 0)
    {
        printf("Entered an nonexistent product code\n");
		modifyStock(productVector);
    }
    else
    {
        printf("Enter the new stock quantity of the product %s with code %d:\n", productVector[position].productName, codeToSearch);
        scanf("%d", &productVector[position].stock);
    }
    system("pause");
}


void modifyProductData(Product productVector[])
{
	system("cls");
    int i, input, codeToSearch, position;
    position = 0;
    input = 0;
    i = 0;
    p("Enter the code of the product whose data you want to modify\n");
    s("%d", &codeToSearch);

    while (input == 0 && i < PRODUCT_COUNT)
    {
        if (productVector[i].productCode == codeToSearch)
        {
            position = i;
            input = 1;
        }
        i++;
    }

    if (input == 0)
    {
        printf("Entered an nonexistent product code\n");
		system("pause");
		modifyProductData(productVector);
    }
    else
    {
		printf("Enter the new name of the product %s with code %d:\n", productVector[position].productName, codeToSearch);
        getchar();
		gets(productVector[position].productName);
		printf("The new name of the product is %s, the product code still is %d and the stock is %d\n",productVector[position].productName, codeToSearch, productVector[position].stock);
		system("pause");
    }
}

void deleteProduct(Product productVector[], int *productCounter)
{
	system("cls");
    int i, input, codeToSearch, position;
    char choice = ' ';
	position = 0;
    input = 0;
    i = 0;
    p("Enter the code of the product whose data you want to DELETE\n");
    s("%d", &codeToSearch);

    while (input == 0 && i < PRODUCT_COUNT)
    {
        if (productVector[i].productCode == codeToSearch)
        {
            position = i;
            input = 1;
        }
        i++;
    }

    if (input == 0)
    {
        printf("Entered an nonexistent product code\n");
		system("pause");
		deleteProduct(productVector, productCounter);
	}
	else
	{
		do
        {
            printf("Are you sure you want to the delete the product code %d, which name is %s and which stock is %d\n(Y/N)", productVector[position].productCode, productVector[position].productName,productVector[position].stock);
	    	getchar();
		    gets(&choice);
            choice = tolower(choice);
        } while (choice != 'y' && choice != 'n');
        if (choice == 'y')
        {
            productVector[position].productCode = 0;
            strcpy(productVector[position].productName, "");
            productVector[position].stock = 0;
            productVector[position].soldQuantity = 0;
          
            int j;
            for (j = position ; j < *productCounter-1 ; j++)
            {
                productVector[j] =  productVector[j+1];
                //productVector[j].productCode = productVector[j+1].productCode;
                //strcpy(productVector[j].productName,productVector[j+1].productName );
                //productVector[j].stock = productVector[j+1].stock;
                //productVector[j].soldQuantity = productVector[j+1].soldQuantity;
            }
            (*productCounter)--;
            //*deletedCode = codeToSearch;  
        }    
    }
}



void addSale(Sale saleVector[], Product productVector[], int salesCounter)
{
    int productCode;
	int i = 0;
    
	printf("Enter the code of the product sold\n");
	scanf("%d",& productCode);
	while (i < PRODUCT_COUNT && productVector[i].productCode != productCode)
    {
        i++;
    }

    if (i == PRODUCT_COUNT)
    {
        printf("Entered a nonexistent product code\n");
        // system("pause");
       	addSale(saleVector, productVector, salesCounter);
    }
    else
    {
        printf("Enter the quantity sold of the product\n");
		scanf("%d", &saleVector[salesCounter].quantity);
        if (saleVector[salesCounter].quantity > productVector[i].stock)
        {
            printf("Trying to sell more units than available\n");
            printf("Product %s, Available units: %d\n", productVector[i].productName, productVector[i].stock);
            system("pause");
            addSale(saleVector, productVector, salesCounter);
        }
        else
        {
            productVector[i].stock -= saleVector[salesCounter].quantity;
            productVector[i].soldQuantity += saleVector[salesCounter].quantity;
            printf("Enter the number of the day of the sale\n");
			scanf("%d", &saleVector[salesCounter].selldate.day);
			printf("Enter the number of the month of the sale\n");
			scanf("%d", &saleVector[salesCounter].selldate.month);
			printf("Enter the year of the sale in 2 digits\n");
			scanf("%d", &saleVector[salesCounter].selldate.year);
			salesCounter++;
        }
    }
}
