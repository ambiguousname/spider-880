import sqlite3
from numpy import random, delete, clip
from enum import IntEnum
from faker import Faker # https://faker.readthedocs.io/en/master/
import time
from math import pow, sqrt, floor
Faker.seed(time.time())
fake = Faker()

class HouseholdConstraint():
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		pass
	@staticmethod
	def constrain(citizens, other_citizens=None):
		pass

class OlderThanZero(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		for citizen in citizens:
			if citizen.age < 0:
				return False
		return True

	@staticmethod
	def constrain(citizens, other_citizens=None):
		for citizen in citizens:
			citizen.age = abs(citizen.age)

class YoungerThan(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		for citizen in citizens:
			if citizen.age > other_citizens[0].age:
				return False
		return True
	@staticmethod
	def constrain(citizens, other_citizens=None):
		for citizen in citizens:
			citizen.age = round(other_citizens[0].age - random.normal(20))
		if not OlderThanZero.is_constrainted(citizens):
			OlderThanZero.constrain(citizens)

class ChildrenMakeNoMoney(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		for citizen in citizens:
			if citizen.age < 18 and citizen.income > 0:
				return False
	
	@staticmethod
	def constrain(citizens, other_citizens=None):
		for citizen in citizens:
			if citizen.age < 18:
				citizen.income = 0

class Family(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		for citizen in citizens:
			if other_citizens[0].last_name != citizen.last_name:
				return False
		return YoungerThan.is_constrainted(citizens, other_citizens) and ChildrenMakeNoMoney.is_constrainted(citizens + other_citizens)
	
	@staticmethod
	def constrain(citizens, other_citizens=None):
		last_name = other_citizens[0].last_name
		for citizen in citizens:
			citizen.last_name = last_name
		if not YoungerThan.is_constrainted(citizens, other_citizens):
			YoungerThan.constrain(citizens, other_citizens)
		if not ChildrenMakeNoMoney.is_constrainted(citizens + other_citizens):
			ChildrenMakeNoMoney.constrain(citizens + other_citizens)

class OverEighteen(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens):
		for citizen in citizens:
			if citizen.age < 18:
				return False
		return True
	
	@staticmethod
	def constrain(citizens):
		for citizen in citizens:
			if citizen.age < 18:
				citizen.age = citizen.age + 18

class AtLeastOne(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, constraint):
		for citizen in citizens:
			if constraint.is_constrainted(citizen):
				return True
		return False

	@staticmethod
	def constrain(citizens, constraint):
		constraint.constrain([random.choice(citizens)])

class SimilarAges(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens):
		return sqrt(pow(citizens[0].age - other_citizens[0].age, 2)) <= sqrt(pow(citizens[0].age - ((citizens[0].age/2) + 7), 2))

	def constrain(citizens, other_citizens):
		citizens[0].age = (other_citizens[0].age/2) + 7

class Married(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens):
		for citizen in citizens + other_citizens:
			if not hasattr(citizen, "spouse"):
				return False
		return Family.is_constrained(citizens, other_citizens) and SimilarAges.is_constrainted(citizens, other_citizens) and OverEighteen.is_constrainted(citizens + other_citizens)

	@staticmethod
	def constrain(citizens, other_citizens=None):
		if not Family.is_constrainted(citizens, other_citizens):
			Family.constrain(citizens, other_citizens)
		if not SimilarAges.is_constrainted(citizens, other_citizens):
			SimilarAges.constrain(citizens, other_citizens)
		if not OverEighteen.is_constrainted(citizens + other_citizens):
			OverEighteen.constrain(citizens + other_citizens)
		
		citizens[0].spouse = other_citizens[0].id
		other_citizens[0].spouse = citizens[0].id

class MarriedHousehold(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		spouses = []
		for citizen in citizens:
			if hasattr(citizen, "spouse"):
				spouses.append(citizen)
		return len(spouses) == 2 and Married.is_constrainted(spouses[0], spouses[1]) and Family.is_constrainted(citizens)
	@staticmethod
	def constrain(citizens, other_citizens=None):
		to_marry = random.choice(citizens, 2, replace=False)
		Married.constrain([to_marry[0]], [to_marry[1]])
		remaining = list(citizens)
		del remaining[remaining.index(to_marry[0])]
		del remaining[remaining.index(to_marry[1])]
		Family.constrain(remaining, [to_marry[0]])

class NonMarriedFamily(HouseholdConstraint):
	@staticmethod
	def is_constrainted(citizens, other_citizens=None):
		copy = list(citizens)
		del copy[0]
		return Family.is_constrainted(copy, [citizens[0]]) and AtLeastOne.is_constrainted(citizens, OverEighteen)
	
	@staticmethod
	def constrain(citizens, other_citizens=None):
		copy = list(citizens)
		del copy[0]
		Family.constrain(copy, [citizens[0]])
		AtLeastOne.constrain(citizens, OverEighteen)

citizen_id = 0
class Citizen():
	def set_vals(self, age, first_name, last_name, income, spouse):
		self.first_name = first_name
		self.last_name = last_name
		self.spouse = spouse
		if self.spouse == "NEXT":
			self.spouse = self.id + 1
		elif self.spouse == "PREV":
			self.spouse = self.id - 1
		self.age = age
		self.income = income
	
	def __init__(self, household, *args):
		global citizen_id
		self.id = citizen_id
		citizen_id += 1
		self.household = household
		if len(args) > 0:
			self.set_vals(*args)
			return
		self.first_name = fake.first_name()
		self.last_name = fake.last_name()
		self.spouse = "NULL"
		self.age = round(abs(random.normal(22, 18)))
		self.income = round(abs(random.normal(10000, 5000)))

	def get_tuple(self):
		return (self.id, floor(self.age), self.first_name, self.last_name, floor(self.income), self.household.household_id, self.spouse)

	def __str__(self):
		return str(self.get_tuple())

class FamilyTypes(IntEnum):
	MARRIED_FAMILY=0, #If there is a couple married. Family (i.e., kids) may also be present.
	NOT_MARRIED_FAMILY=1, #A couple that isn't married, and may also have kids.
	LIVING_ALONE=2, # Self explanatory.
	NOT_LIVING_ALONE=3 # Shared household where no one is a couple.
	# This ignores weird edge cases like couples living with others, but again. Edge cases.

household_id = 0

class Household():
	def set_vals(self, citizens : list[Citizen], family_type : FamilyTypes, zip : int):
		self.citizens = citizens
		self.family_type = family_type
		self.zip = zip
	
	def __init__(self, citizens=None, *args):
		global household_id
		self.household_id = household_id
		household_id += 1
		if len(args) > 0:
			self.set_vals(citizens, *args)
			return
		self.family_type = random.choice([FamilyTypes.MARRIED_FAMILY, FamilyTypes.NOT_MARRIED_FAMILY, FamilyTypes.LIVING_ALONE, FamilyTypes.NOT_LIVING_ALONE], p=[0.55, 0.16, 0.24, 0.05])
		self.citizens = []
		num_occupants = 1
		if self.family_type == FamilyTypes.NOT_LIVING_ALONE:
			num_occupants = max(round(random.normal(2.63)), 2)
		
		if self.family_type == FamilyTypes.MARRIED_FAMILY or self.family_type == FamilyTypes.NOT_MARRIED_FAMILY:
			num_occupants = max(round(random.normal(3.16)), 2)
		
		for i in range(num_occupants):
			self.citizens.append(Citizen(self))
		
		if self.family_type == FamilyTypes.MARRIED_FAMILY:
			MarriedHousehold.constrain(self.citizens)
		elif self.family_type == FamilyTypes.NOT_MARRIED_FAMILY:
			NonMarriedFamily.constrain(self.citizens)
		elif self.family_type == FamilyTypes.NOT_LIVING_ALONE:
			OverEighteen.constrain(self.citizens)
			ChildrenMakeNoMoney.constrain(self.citizens)
		
		self.zip = floor(random.uniform(0, 999))
	
	def __str__(self) -> str:
		house_str = "Household " + str(self.household_id) + ": Type " + str(self.family_type) + " - \n"
		for citizen in self.citizens:
			house_str += str(citizen) + "\n"
		house_str += "----"
		return house_str
	
	def get_tuple(self):
		return (self.household_id, int(self.family_type), self.zip)


class CitizensDB():
	def __init__(self):
		self.households = []
		self.toAppend = []
	
	def generate(self, toAppend: list[tuple[tuple, list[tuple]]]):
		sample_loc = random.standard_normal(len(toAppend))
		sample_loc = clip(abs(sample_loc/2), 0, 1)
		sample_loc.sort()
		town_size = round(random.uniform(200, 300))
		random.shuffle(toAppend)
		for i in range(town_size):
			while (len(sample_loc) > 0 and sample_loc[0] <= i/(town_size - 1)):
				household_args, citizens_list = toAppend.pop()
				sample_loc = delete(sample_loc, 0)
				citizens = []
				for citizen_args in citizens_list:
					citizens.append(Citizen(None, *citizen_args))
				
				household = Household(citizens, *household_args)

				for citizen in citizens:
					citizen.household = household

				self.households.append(household)
				print(str(household))
			self.households.append(Household())
		print("Generated", len(self.households), "households.")
		

	def writeValues(self, cursor):
		for household in self.households:
			cursor.executemany("INSERT INTO households (id, family_status, zip) VALUES (?, ?, ?)", [household.get_tuple()])
			tuples = []
			for citizen in household.citizens:
				tuples.append(citizen.get_tuple())
			cursor.executemany("INSERT INTO citizens (id, age, first_name, last_name, income, household_id, spouse_id) VALUES(?, ?, ?, ?, ?, ?, ?);", tuples)

if __name__ == "__main__":
	citizens = CitizensDB()
	to_add = [
		((FamilyTypes.NOT_LIVING_ALONE, 180),
		[
			(35, "Jerry", "Seinfeld", 3512, "NULL"),
			(30, "George", "Costanza", 5542, "NULL"),
			(28, "Elaine", "Benes", 6120, "NULL"),
			(40, "Cosmo", "Kramer", 0, 69)
		]),
		((FamilyTypes.LIVING_ALONE, 538), 
		[
			(32, "Jessica", "Reyes", 4223, "NULL")
		]),
		((FamilyTypes.MARRIED_FAMILY), 439),
		[
			(60, "Brian", "Gertwig", 2342, "NEXT"),
			(59, "Yvonne", "Gertwig", 6428, "PREV")
		],
		((FamilyTypes.NOT_LIVING_ALONE, 531),
   		[
			(30, "Lucas", "Friedrich", 6105, "NULL"),
			(22, "Emilie", "Quantz", 4200, "NULL"),
			(31, "Elizabeth", "Parton", 4239, "NULL"),
		]),
	]
	citizens.generate(to_add)
	db = sqlite3.connect("citizens.db")
	cursor = db.cursor()
	cursor.execute("DROP TABLE IF EXISTS citizens;")
	cursor.execute("DROP TABLE IF EXISTS households;")
	cursor.execute("""CREATE TABLE citizens (
			id INT PRIMARY KEY,
			age INT CHECK(age >= 0),
			first_name TEXT NOT NULL,
			last_name TEXT NOT NULL,
			income INT NOT NULL,
			household_id INT,
			spouse_id INT,
			FOREIGN KEY(household_id) REFERENCES households(id)
	)""")
	cursor.execute("""CREATE TABLE households (
			id INT PRIMARY KEY,
			family_status INT NOT NULL CHECK(family_status >= 0 AND family_status <= 3), -- 0: Married w/ Family, 1: Not Married w/ Family, 2: Living Alone, 3: Not Living Alone without family.
			zip INT NOT NULL CHECK(zip >= 0 AND zip <= 1000) -- Represent as XYZ, where X is the area, Y is the subarea, and Z is the district.
	);""")
	citizens.writeValues(cursor)
	db.commit()

	db.close()
