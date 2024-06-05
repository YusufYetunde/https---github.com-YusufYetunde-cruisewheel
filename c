"use client";
import { getDistance } from "../lib/distance";
import { PaymentMethod } from "../lib/strip";
import { useRouter } from "next/navigation";
import React, { useEffect, useState } from "react";

import { differenceInDays } from "date-fns";

const StepFour = ({ form }) => {
  const router = useRouter();
  const {
    imgUrl,
    transfertype,
    title,
    firstname,
    lastname,
    email,
    phoneNumber,
    comment,
    source,
    destination,
    price: initialPrice,
    pickupdate,
    returndate,
  } = form.getValues();
  const [price, setPrice] = useState(initialPrice);

  useEffect(() => {
    if (pickupdate && returndate) {
      const daysDifference = differenceInDays(new Date(returndate), new Date(pickupdate));
      const finalPrice = initialPrice * daysDifference;
      setPrice(finalPrice);
    }
  }, [pickupdate, returndate, initialPrice]);

  const Submit = async () => {
    const url = await PaymentMethod({ ...form.getValues(), price });
    router.push(url);
  };

  return (
    <div className="max-w-[1150px] mx-auto">
      <div className="grid grid-cols-1 p-4 mt-10">
        <div className="relative w-full mb-4 rounded overflow-hidden">
          <img src={imgUrl} className="object-cover" alt="" />
        </div>
        <div className="pt-8">
          <div className="flex justify-between items-center border-b mb-5 pb-5">
            <h3 className="text-3xl font-bold ">{title}</h3>
            <p className="text-lg font-bold">
              Price: <span className="text-2xl">${price}</span>
            </p>
          </div>
          <h3 className="text-2xl font-bold mb-5">Order Information</h3>
          <div className="grid grid-cols-1 md:grid-cols-2 bg-slate-50 p-5 rounded-lg mb-8">
            <div className="flex justify-between p-2">
              <span className="font-bold">First Name:</span>
              <span>{firstname}</span>
            </div>
            <div className="flex justify-between p-2">
              <span className="font-bold">Last Name:</span>
              <span>{lastname}</span>
            </div>
            <div className="flex justify-between p-2">
              <span className="font-bold">Email:</span>
              <span>{email}</span>
            </div>
            <div className="flex justify-between p-2">
              <span className="font-bold">Phone Number:</span>
              <span>{phoneNumber}</span>
            </div>
            <div className="flex justify-between p-2">
              <span className="font-bold">Comment:</span>
              <span>{comment}</span>
            </div>
          </div>

          <button
            className="bg-third-color text-white font-bold w-full py-2.5 px-4 rounded-md"
            onClick={Submit}
          >
            Pay Now
          </button>
        </div>
      </div>
    </div>
  );
};

export default StepFour;
