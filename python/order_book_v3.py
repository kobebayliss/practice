from sortedcontainers import SortedDict

class Node:
    def __init__(self, id, next=None, prev=None):
        self.id = id
        self.next = next
        self.prev = prev
    
    def __str__(self):
        return f"{self.id}"

class orderNode:
    def __init__(self, id, side, price, quantity, node):
        self.id = id
        self.side = side
        self.price = price
        self.quantity = quantity
        self.node = node

class priceLevel:
    def __init__(self, quantity, head, tail):
        self.quantity = quantity
        self.head = head
        self.tail = tail

    def __str__(self):
        return f"{self.quantity} units, {self.head} to {self.tail}"

class orderBook:
    def __init__(self):
        self.buy_orders = SortedDict()       # price: priceLevel
        self.sell_orders = SortedDict()      # price: priceLevel
        self.orders = {}                     # order_id: orderNode

    def place_order(self, order_id, side, price, quantity):
        dic = self.buy_orders if side == "buy" else self.sell_orders
        node = Node(order_id)
        if price not in dic:
            dic[price] = priceLevel(quantity, node, node)
        else:
            price_level = dic[price]
            price_level.quantity += quantity
            price_level.tail.next = node
            price_level.tail = node
        self.orders[order_id] = orderNode(order_id, side, price, quantity, node)
        return self.buy_orders[price]
    
    def cancel_order(self, order_id):
        order_node = self.orders[order_id]
        dic = self.buy_orders if order_node.side == "buy" else self.sell_orders
        node = order_node.node
        if node.prev:
            if node.next:
                node.prev.next = node.next
                node.next.prev = node.prev
            else:
                node.prev.next = None
        elif node.next:
            node.next.prev = None
        if not node.next and not node.prev:
            dic.pop(order_node.price)
        else:
            price_level = dic[order_node.price]
            price_level.quantity -= order_node.quantity
        node.prev = None
        node.next = None
        node = None
        del self.orders[order_id]
        return True
    
    def get_volume_at_price(self, side, price):
        dic = self.buy_orders if side == "buy" else self.sell_orders
        price_level = dic[price]
        return price_level.quantity

bk = orderBook()
print(bk.place_order(1, "buy", 400.0, 30.0))
print(bk.place_order(2, "buy", 400.0, 20.0))
print(bk.place_order(3, "buy", 402.0, 15.0))
print(bk.place_order(4, "buy", 402.0, 25.0))
print(bk.place_order(5, "buy", 400.0, 10.0))
print(bk.cancel_order(2))
print(bk.get_volume_at_price("buy", 400.0))