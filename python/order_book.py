import heapq

class OrderBook:
    def __init__(self):
        self.orders = {}                   # order id: (price, quantity)
        self.price_to_quantity = {}        # price: quantity of orders at given price
        self.heap = []                     # max heap of prices

    def add_order(self, order_id, price, quantity):
        # O(log n)
        if order_id not in self.orders:
            self.orders[order_id] = (price, quantity)
            if price not in self.price_to_quantity:
                heapq.heappush_max(self.heap, price)
                self.price_to_quantity[price] = quantity
            else:
                self.price_to_quantity[price] += quantity

    def cancel_order(self, order_id):
        # O(1)
        if order_id not in self.orders:
            return False
        price, quantity = self.orders[order_id]
        self.price_to_quantity[price] -= quantity
        if self.price_to_quantity[price] == 0:
            del self.price_to_quantity[price]
        del self.orders[order_id]
        return True

    def get_best_price(self):
        # O(1)
        if not self.orders:
            return None
        while self.heap:
            if self.heap[0] in self.price_to_quantity:
                return self.heap[0]
            else:
                heapq.heappop_max(self.heap)
        return None

    def get_total_quantity_at_price(self, price):
        # O(1)
        if price not in self.price_to_quantity:
            return 0
        return self.price_to_quantity[price]
    
    def update_order(self, order_id, new_price=None, new_quantity=None):
        # O(1)
        if order_id not in self.orders:
            return False
        old_price, old_quantity = self.orders[order_id]
        if new_price is not None:
            if new_price not in self.price_to_quantity:
                heapq.heappush_max(self.heap, new_price)
                self.price_to_quantity[new_price] = 0
            if new_quantity is not None:
                self.orders[order_id] = (new_price, new_quantity)
                self.price_to_quantity[new_price] += new_quantity
            else:
                self.orders[order_id] = (new_price, old_quantity)
                self.price_to_quantity[new_price] += old_quantity
            self.price_to_quantity[old_price] -= old_quantity
        elif new_quantity is not None:
            self.orders[order_id] = (old_price, new_quantity)
            self.price_to_quantity[old_price] -= old_quantity
            self.price_to_quantity[old_price] += new_quantity
        if self.price_to_quantity[old_price] == 0:
            del self.price_to_quantity[old_price]
        return True
    
    def get_top_k_prices(self, k):
        # O(k log n)
        result = []
        temp = []
        while self.heap and len(result) < k:
            top_price = heapq.heappop_max(self.heap)
            if top_price in self.price_to_quantity:
                result.append(top_price)
                temp.append(top_price)
        for price in temp:
            heapq.heappush_max(self.heap, price)
        return result
        
    
order = OrderBook()
order.add_order(1, 50, 300)
order.add_order(2, 55, 250)
order.add_order(3, 60, 500)
order.add_order(4, 50, 1000)
print(order.get_best_price())
order.cancel_order(3)
print(order.get_best_price())
print(order.get_total_quantity_at_price(50))
print(order.update_order(4, 70, 1500))
print(order.get_best_price())
print(order.get_total_quantity_at_price(50))
order.add_order(5, 55, 100)
order.add_order(6, 55, 60)
print(order.get_top_k_prices(3))